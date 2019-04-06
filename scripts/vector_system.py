from SFGE import *


class VectorSystem(System):
    t = 0.0
    rotation_speed = 0.0

    def init(self):
        self.t = 0.0
        self.rotation_speed = 45.0

    def update(self, dt):
        self.t += dt

    def on_draw(self):
        # rotating vector
        v = Vec2f(10, 10)
        v = v.rotate(self.rotation_speed*self.t)

        graphics2d_manager.draw_vector(Vec2f(200,200), v, Color.Green)
