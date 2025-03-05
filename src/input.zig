const std = @import("std");

pub const MouseButton = enum(u32) { Left = 0, Middle = 1, Right = 2 };

const InputNotification = enum(u32) { KeyDown = 0x0100, KeyUp = 0x0101, MouseMove = 0x0200, LeftMouseButtonDown = 0x0201, LeftMouseButtonUp = 0x0202, MiddleMouseButtonDown = 0x0207, MiddleMouseButtonUp = 0x0208, RightMouseButtonDown = 0x0204, RightMouseButtonUp = 0x0205, _ };

/// Extract the lower 16 bits (unsigned) of a 32-bit value.
fn lowWord(value: u32) u16 {
    return @intCast(value & 0xFFFF);
}

/// Extract the upper 16 bits (unsigned) of a 32-bit value.
fn highWord(value: u32) u16 {
    return @intCast((value >> 16) & 0xFFFF);
}

/// Interpret the lower 16 bits as a signed 16-bit integer (used for X coordinates).
fn getXParam(lparam: usize) i16 {
    // Truncate lparam to 32 bits, then cast the low word to signed 16-bit.
    const as_u32: u32 = @intCast(lparam & 0xFFFF_FFFF);
    return @intCast(as_u32 & 0xFFFF);
}

/// Interpret the higher 16 bits as a signed 16-bit integer (used for Y coordinates).
fn getYParam(lparam: usize) i16 {
    const as_u32: u32 = @intCast(lparam & 0xFFFF_FFFF);
    return @intCast((as_u32 >> 16) & 0xFFFF);
}

pub const InputState = struct {
    keys: [256]bool,
    keysDown: [256]bool,
    keysUp: [256]bool,
    mouseX: i32,
    mouseY: i32,
    mouseButtonsDown: [3]bool,
    mouseButtons: [3]bool,
    mouseButtonsUp: [3]bool,

    pub fn init() InputState {
        return InputState{ .keys = std.mem.zeroes([256]bool), .keysDown = std.mem.zeroes([256]bool), .keysUp = std.mem.zeroes([256]bool), .mouseX = 0, .mouseY = 0, .mouseButtons = std.mem.zeroes([3]bool), .mouseButtonsDown = std.mem.zeroes([3]bool), .mouseButtonsUp = std.mem.zeroes([3]bool) };
    }

    pub fn key(self: *InputState, code: u8) bool {
        return self.keys[code];
    }

    pub fn keyDown(self: *InputState, code: u8) bool {
        return self.keysDown[code];
    }

    pub fn keyUp(self: *InputState, code: u8) bool {
        return self.keysUp[code];
    }

    pub fn mouseButton(self: *InputState, button: MouseButton) bool {
        return self.mouseButtons[button];
    }

    pub fn mouseButtonDown(self: *InputState, button: MouseButton) bool {
        return self.mouseButtonsDown[button];
    }

    pub fn mouseButtonUp(self: *InputState, button: MouseButton) bool {
        return self.mouseButtonsUp[button];
    }

    pub fn clear(self: *InputState) void {
        @memset(&self.keysDown, false);
        @memset(&self.keysUp, false);
        @memset(&self.mouseButtonsDown, false);
        @memset(&self.mouseButtonsUp, false);
    }

    pub fn handleWindowEvent(self: *InputState, msg: InputNotification, wParam: usize, lParam: usize) bool {
        switch (msg) {
            InputNotification.KeyDown => {
                if (wParam < 256) {
                    self.keysDown[wParam] = true;
                    self.keys[wParam] = true;
                }
            },
            InputNotification.KeyUp => {
                if (wParam < 256) {
                    self.keysUp[wParam] = false;
                    self.keys[wParam] = false;
                }
            },
            InputNotification.LeftMouseButtonDown => {
                self.mouseButtons[0] = true;
                self.mouseButtonsDown[0] = true;
            },
            InputNotification.LeftMouseButtonUp => {
                self.mouseButtons[0] = false;
                self.mouseButtonsUp[0] = true;
            },
            InputNotification.MiddleMouseButtonDown => {
                self.mouseButtons[1] = false;
                self.mouseButtonsUp[1] = true;
            },
            InputNotification.MiddleMouseButtonUp => {
                self.mouseButtons[1] = false;
                self.mouseButtonsUp[1] = true;
            },
            InputNotification.RightMouseButtonDown => {
                self.mouseButtons[2] = true;
                self.mouseButtonsDown[2] = true;
            },
            InputNotification.RightMouseButtonUp => {
                self.mouseButtons[2] = false;
                self.mouseButtonsUp[2] = true;
            },
            InputNotification.MouseMove => {
                const x = getXParam(lParam);
                const y = getYParam(lParam);
                self.mouseX = @intCast(x);
                self.mouseY = @intCast(y);
            },
            else => {
                return false;
            },
        }

        return true;
    }
};
