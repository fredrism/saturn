const std = @import("std");
const c = @cImport({
    @cDefine("_WIN32", "1");
    // Optionally reduce the size of windows.h:
    @cDefine("WIN32_LEAN_AND_MEAN", "1");
    @cInclude("windows.h");
    @cInclude("glad/glad.h");
    @cInclude("glad/glad_wgl.h");
});

const shaders = @import("shaders.zig");
const renderer = @import("renderer.zig");

pub const Error = error{
    FailedToGetModuleHandle,
    FailedToRegisterClass,
    FailedToCreateWindow,
    FailedToGetDC,
    FailedToChoosePixelFormat,
    FailedToSetPixelFormat,
    FailedToCreateTempContext,
    FailedToMakeTempContextCurrent,
    FailedToLoadWGL,
    FailedToCreateContextAttribs,
    FailedToMakeNewContextCurrent,
    FailedToLoadGL,
};

fn WndProc(hWnd: c.HWND, msg: c.UINT, wParam: c.WPARAM, lParam: c.LPARAM) callconv(.C) c.LRESULT {
    switch (msg) {
        c.WM_DESTROY => {
            c.PostQuitMessage(0);
            return 0;
        },
        else => return c.DefWindowProcA(hWnd, msg, wParam, lParam),
    }
}

pub fn main() !void {
    // Get our HINSTANCE
    const hInstance = c.GetModuleHandleA(null);
    if (hInstance == 0) return Error.FailedToGetModuleHandle;

    // Register a window class
    const className = "ZigWinApiGL";
    var wc: c.WNDCLASSEXA = .{
        .cbSize = @sizeOf(c.WNDCLASSEXA),
        .style = 0,
        .lpfnWndProc = WndProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance,
        .hIcon = null,
        .hCursor = c.LoadCursorA(null, c.IDC_ARROW),
        .hbrBackground = null,
        .lpszMenuName = null,
        .lpszClassName = &className[0],
        .hIconSm = null,
    };
    if (c.RegisterClassExA(&wc) == 0) {
        return Error.FailedToRegisterClass;
    }

    // Create a window
    const hwnd = c.CreateWindowExA(
        0,
        &className[0],
        "Zig + WinAPI + OpenGL (GLAD)",
        c.WS_OVERLAPPEDWINDOW | c.WS_VISIBLE,
        c.CW_USEDEFAULT,
        c.CW_USEDEFAULT,
        800,
        600,
        null, // hWndParent
        null, // hMenu
        hInstance,
        null, // lpParam
    );
    if (hwnd == null) {
        return Error.FailedToCreateWindow;
    }

    // Grab the device context from our window
    const dc = c.GetDC(hwnd);
    if (dc == null) {
        return Error.FailedToGetDC;
    }

    // Choose a basic pixel format
    var pfd: c.PIXELFORMATDESCRIPTOR = .{
        .nSize = @sizeOf(c.PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = c.PFD_DRAW_TO_WINDOW | c.PFD_SUPPORT_OPENGL | c.PFD_DOUBLEBUFFER,
        .iPixelType = c.PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = c.PFD_MAIN_PLANE,
        // Other fields default to 0
    };

    const formatIndex = c.ChoosePixelFormat(dc, &pfd);
    if (formatIndex == 0) {
        return Error.FailedToChoosePixelFormat;
    }

    if (c.SetPixelFormat(dc, formatIndex, &pfd) == 0) {
        return Error.FailedToSetPixelFormat;
    }

    // Create a temporary legacy OpenGL context so we can load WGL extensions
    const tempRC = c.wglCreateContext(dc);
    if (tempRC == null) {
        return Error.FailedToCreateTempContext;
    }
    defer _ = c.wglDeleteContext(tempRC);

    if (c.wglMakeCurrent(dc, tempRC) == 0) {
        return Error.FailedToMakeTempContextCurrent;
    }

    // Now load WGL extension functions (needed for wglCreateContextAttribsARB, etc.)
    if (c.gladLoadWGL(dc) == 0) {
        return Error.FailedToLoadWGL;
    }

    const newRC = c.wglCreateContext(dc);
    if (newRC == null) {
        return Error.FailedToCreateContextAttribs;
    }

    // Make the new context current
    if (c.wglMakeCurrent(dc, newRC) == 0) {
        return Error.FailedToMakeNewContextCurrent;
    }

    // Load all modern OpenGL functions
    if (c.gladLoadGL() == 0) {
        return Error.FailedToLoadGL;
    }

    const shader = try shaders.testShaders();
    const vao = renderer.setupMesh();

    // Main loop
    var msg: c.MSG = .{};
    while (true) {
        // Process any pending messages
        while (c.PeekMessageA(&msg, null, 0, 0, c.PM_REMOVE) != 0) {
            if (msg.message == c.WM_QUIT) {
                return;
            }
            _ = c.TranslateMessage(&msg);
            _ = c.DispatchMessageA(&msg);
        }

        // Basic clear
        c.glClearColor(0.5, 0.3, 0.3, 1.0);
        c.glClear(c.GL_COLOR_BUFFER_BIT);

        renderer.render(shader, vao);

        // Swap buffers
        _ = c.SwapBuffers(dc);
    }
}

test "simple test" {
    var list = std.ArrayList(i32).init(std.testing.allocator);
    defer list.deinit(); // try commenting this out and see if zig detects the memory leak!
    try list.append(42);
    try std.testing.expectEqual(@as(i32, 42), list.pop());
}
