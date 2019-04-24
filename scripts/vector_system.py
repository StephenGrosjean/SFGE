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



    def init(self):
        self.t = 0.0

    def update(self, dt):
        self.u = Vec2f(10, 15) #Set the graphical Vector
        self.v = Vec2f(30,15)
        self.pu = Physics2dManager.pixel2meter(self.u) #Convert the graphical vector to physical vector
        self.pv = Physics2dManager.pixel2meter(self.v)

        self.res3 = p2Vec2.cross(self.pu, self.pv)
        self.res2 = p2Vec2(self.res3.x, self.res3.y)

        self.result = Physics2dManager.meter2pixel(self.res2)

    def on_draw(self):
        graphics2d_manager.draw_vector(self.u, Vec2f(200,200), Color.Green)
        graphics2d_manager.draw_vector(self.v, Vec2f(200,200), Color.Blue)
        graphics2d_manager.draw_vector(self.result, Vec2f(200,200), Color.Red)


