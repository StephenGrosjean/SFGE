import random
import math
from SFGE import *

body2d_manager = physics2d_manager.body2d_manager
sprite_manager = graphics2d_manager.sprite_manager
texture_manager = graphics2d_manager.texture_manager


class AabbSystem(System):
    screen_size: Vector2f
    entity_nmb = None  # type: int
    gravity: p2Vec2
    mass: int

    def init(self):
        self.gravity = p2Vec2(0 , 9.81)
        self.entity_nmb = 1
        self.screen_size = engine.config.screen_size

        entity_manager.resize(self.entity_nmb)

        for i in range(self.entity_nmb):
            new_entity = entity_manager.create_entity(i+1)

            transform = transform2d_manager.add_component(new_entity)  # type: Transform2d
            transform.position = Vec2f(self.screen_size.x/2, self.screen_size.y/2)
            transform.scale = Vec2f(2,2)
            body2d = body2d_manager.add_component(new_entity)  # type: Body2d

            sprite_manager.create_component(new_entity, "data/sprites/round.png")


    def fixed_update(self):
        for i in range(self.entity_nmb):

            transform = transform2d_manager.get_component(i+1)  # type: Transform2d

            body2d = body2d_manager.get_component(i+1)  # type: Body2d
            bodyp2: p2Body = body2d.get_body()

            aabb: p2AABB = bodyp2.get_AABB()


