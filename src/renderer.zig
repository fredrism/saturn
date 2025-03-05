const std = @import("std");
const c = @cImport({
    @cInclude("glad/glad.h");
});

pub fn setupMesh() c.GLuint {
    // Define a simple triangle (x, y, z)
    const vertices = [_]f32{
        -0.5, -0.5, 0.0,
        0.5,  -0.5, 0.0,
        0.0,  0.5,  0.0,
    };

    // Create VAO
    var vao: c.GLuint = 0;
    c.glGenVertexArrays(1, &vao);
    c.glBindVertexArray(vao);

    // Create VBO
    var vbo: c.GLuint = 0;
    c.glGenBuffers(1, &vbo);
    c.glBindBuffer(c.GL_ARRAY_BUFFER, vbo);
    c.glBufferData(
        c.GL_ARRAY_BUFFER,
        @sizeOf(f32) * vertices.len,
        &vertices,
        c.GL_STATIC_DRAW,
    );

    // Vertex attribute setup (location=0 in our shader)
    c.glEnableVertexAttribArray(0);
    c.glVertexAttribPointer(
        0, // index
        3, // size (x,y,z)
        c.GL_FLOAT, // type
        c.GL_FALSE, // normalized
        3 * @sizeOf(f32), // stride
        null, // pointer offset
    );

    return vao;
}

pub fn render(shaderProg: c.GLuint, vao: c.GLuint) void {
    c.glUseProgram(shaderProg);
    c.glBindVertexArray(vao);
    c.glDrawArrays(c.GL_TRIANGLES, 0, 3);
}
