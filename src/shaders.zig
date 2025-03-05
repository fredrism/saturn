const std = @import("std");
const c = @cImport({
    @cInclude("glad/glad.h");
});

// Compile a single shader (vertex or fragment) from source.
fn compileShader(source: []const u8, shaderType: c.GLenum) !c.GLuint {
    const shader = c.glCreateShader(shaderType);
    if (shader == 0) {
        return error.ShaderCreationFailed;
    }

    // Convert Zig slice to pointer for glShaderSource
    const len: c.GLint = @intCast(source.len);
    std.debug.print("Shader Length: {d}", .{len});
    var src_ptr = &source[0];
    c.glShaderSource(shader, 1, &src_ptr, &len);
    c.glCompileShader(shader);

    // Check for compilation errors
    var status: c.GLint = 0;
    c.glGetShaderiv(shader, c.GL_COMPILE_STATUS, &status);
    if (status == 0) {
        var infoLog: [512]u8 = undefined;
        c.glGetShaderInfoLog(shader, 512, null, &infoLog[0]);
        // Print or log the error
        std.debug.print("Shader error:\n{s}\n", .{infoLog[0..]});
        return error.ShaderCompileFailed;
    }

    return shader;
}

// Link a vertex shader and fragment shader into a program.
fn createShaderProgram(vertexSrc: []const u8, fragmentSrc: []const u8) !c.GLuint {
    // Compile vertex shader
    const vs = try compileShader(vertexSrc, c.GL_VERTEX_SHADER);
    defer c.glDeleteShader(vs);

    // Compile fragment shader
    const fs = try compileShader(fragmentSrc, c.GL_FRAGMENT_SHADER);
    defer c.glDeleteShader(fs);

    // Create program
    const program = c.glCreateProgram();
    if (program == 0) {
        return error.ProgramCreationFailed;
    }

    c.glAttachShader(program, vs);
    c.glAttachShader(program, fs);
    c.glLinkProgram(program);

    // Check for linking errors
    var status: c.GLint = 0;
    c.glGetProgramiv(program, c.GL_LINK_STATUS, &status);
    if (status == 0) {
        var infoLog: [512]u8 = undefined;
        c.glGetProgramInfoLog(program, 512, null, &infoLog[0]);
        // Print or log the error
        std.debug.print("Program link error:\n{any}\n", .{infoLog[0..]});
        c.glDeleteProgram(program);
        return error.ProgramLinkFailed;
    }

    return program;
}

pub fn testShaders() !c.GLuint {
    // After you have a valid OpenGL context and called gladLoadGL()...
    const vertexShaderSrc =
        \\#version 330 core
        \\layout (location = 0) in vec3 aPos;
        \\void main() {
        \\    gl_Position = vec4(aPos, 1.0);
        \\}
    ;

    const fragmentShaderSrc =
        \\#version 330 core
        \\out vec4 FragColor;
        \\void main() {
        \\    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        \\}
    ;

    return try createShaderProgram(vertexShaderSrc, fragmentShaderSrc);
}

pub const ShaderProgram = struct {
    program: c.GLuint,

    pub fn init(vertexSrc: []const u8, fragmentSrc: []const u8) !ShaderProgram {
        const program = try createShaderProgram(vertexSrc, fragmentSrc);
        return .{ .program = program };
    }

    pub fn deinit(self: *ShaderProgram) void {
        c.glDeleteProgram(self.program);
        self.program = 0;
    }

    pub fn use(self: *ShaderProgram) void {
        c.glUseProgram(self.program);
    }
};
