from SFGE import *


class VectorSystem(System):
    t = 0.0
	#Graphical Vectors
    u = Vec2f()
    v = Vec2f()
    result = Vec2f()

	#Physical Vectors
    pu = p2Vec2()
    pv = p2Vec2()

    sign = int


    def init(self):
        self.t = 0.0
        self.sign = 1

    def update(self, dt):
        self.t += self.sign * dt
        self.u = Vec2f(12, -5) #Set the graphical Vector
        self.v = Vec2f(5,5)
        self.pu = Physics2dManager.pixel2meter(self.u) #Convert the graphical vector to physical vector
        self.pv = Physics2dManager.pixel2meter(self.v)

        self.res = p2Vec2.lerp(self.pu, self.pv, self.t)

        self.result = Physics2dManager.meter2pixel(self.res)

        self.angle = p2Vec2.angle_between(self.res, self.pv, 1)
        print(self.angle)





        if self.t > 1:
            self.sign = -1

        if self.t <= 0:
            self.sign = 1



    def on_draw(self):
        graphics2d_manager.draw_vector(self.u, Vec2f(200,200), Color.Green)
        graphics2d_manager.draw_vector(self.v, Vec2f(200,200), Color.Blue)
        graphics2d_manager.draw_vector(self.result, Vec2f(200,200), Color.Red)
