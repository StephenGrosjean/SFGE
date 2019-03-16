from SFGE import *

shape_manager = graphics2d_manager.shape_manager


class ContactDebugSystem(System):

    def init(self):
        entities = entity_manager.get_entities_with_type(System.Shape)
        for entity in entities:
            shape = shape_manager.get_component(entity)
            shape.set_fill_color(Color.Red)

    def on_contact(self, c1, c2, enter):
        print("Contact between {0} and {1} with enter: {2}".format(str(c1), str(c2), str(enter)))
        if enter:
            shape1 = shape_manager.get_component(c1.entity)
            if shape1 is not None:
                shape1.set_fill_color(Color.Green)
            shape2 = shape_manager.get_component(c2.entity)
            if shape2 is not None:
                shape2.set_fill_color(Color.Green)
        else:
            shape1 = shape_manager.get_component(c1.entity)
            if shape1 is not None:
                shape1.set_fill_color(Color.Red)
            shape2 = shape_manager.get_component(c2.entity)
            if shape2 is not None:
                shape2.set_fill_color(Color.Red)

