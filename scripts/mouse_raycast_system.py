from SFGE import *


class MouseRaycastSystem(System):
    def init(self):
        self.ray_nmb = 6
        self.angles = [360/6*i for i in range(6)]

    def fixed_update(self):
        mouse_pos = input_manager.mouse.position

    def update(self):
        pass
