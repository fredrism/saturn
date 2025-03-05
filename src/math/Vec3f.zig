const Vec3f = struct {
    x: f32,
    y: f32,
    z: f32,

    pub fn add(self: *Vec3f, rhs: Vec3f) *Vec3f {
        self.x += rhs.x;
        self.y += rhs.y;
        self.z += rhs.z;

        return self;
    }
};
