/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <engine/engine.h>
#include <engine/scene.h>
#include <gtest/gtest.h>
#include "graphics/shape2d.h"
#include "physics/collider2d.h"

TEST(Physics, TestBounce)
{
	sfge::Engine engine;

	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	config->gravity = p2Vec2(0, 9.81f);
	config->maxFramerate = 60;
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Test Bounce";

//STATIC ENTITIES
	json groundEntity;
	groundEntity["name"] = "Ground";

	json groundTransform;
	groundTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	groundTransform["position"] = { 480,600 };
	groundTransform["scale"] = { 1.0,1.0 };
	groundTransform["angle"] = 0.0;

	json groundShape;
	groundShape["name"] = "Rect Shape Component";
	groundShape["type"] = sfge::ComponentType::SHAPE2D;
	groundShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	groundShape["size"] = { 1000,100 };

	json groundRigidBody;
	groundRigidBody["name"] = "Rigidbody";
	groundRigidBody["type"] = sfge::ComponentType::BODY2D;
	groundRigidBody["body_type"] = p2BodyType::STATIC;

	json groundCollider;
	groundCollider["name"] = "Rect Collider";
	groundCollider["type"] = sfge::ComponentType::COLLIDER2D;
	groundCollider["collider_type"] = sfge::ColliderType::BOX;
	groundCollider["size"] = { 1000,100 };
	groundCollider["sensor"] = false;

	groundEntity["components"] = { groundTransform, groundShape, groundRigidBody, groundCollider };

//END STATIC ENTITIES

//DYNAMIC ENTITIES
	json circleEntity;
	circleEntity["name"] = "DynamicCircle1";

	json circleTransform;
	circleTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform["position"] = { 300,200 };
	circleTransform["scale"] = { 1.0,1.0 };
	circleTransform["angle"] = 0.0;

	json circleShape;
	circleShape["name"] = "Circle Shape Component";
	circleShape["type"] = sfge::ComponentType::SHAPE2D;
	circleShape["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape["radius"] = 30;

	json circleCollider;
	circleCollider["name"] = "Circle Collider";
	circleCollider["type"] = sfge::ComponentType::COLLIDER2D;
	circleCollider["collider_type"] = sfge::ColliderType::CIRCLE;
	circleCollider["radius"] = 30;
	circleCollider["bouncing"] = 0;
	circleCollider["sensor"] = false;

	json circleRigidBody;
	circleRigidBody["name"] = "Rigidbody";
	circleRigidBody["type"] = sfge::ComponentType::BODY2D;
	circleRigidBody["body_type"] = p2BodyType::DYNAMIC;
	circleRigidBody["mass"] = 1;

	circleEntity["components"] = { circleTransform, circleShape, circleRigidBody, circleCollider };

	json circleEntity2;
	circleEntity2["name"] = "DynamicCircle2";

	json circleTransform2;
	circleTransform2["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform2["position"] = { 400, 200 };
	circleTransform2["scale"] = { 1.0,1.0 };
	circleTransform2["angle"] = 0.0;

	json circleShape2;
	circleShape2["name"] = "Circle Shape Component";
	circleShape2["type"] = sfge::ComponentType::SHAPE2D;
	circleShape2["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape2["radius"] = 30;

	json circleCollider2;
	circleCollider2["name"] = "Circle Collider";
	circleCollider2["type"] = sfge::ComponentType::COLLIDER2D;
	circleCollider2["collider_type"] = sfge::ColliderType::CIRCLE;
	circleCollider2["radius"] = 30;
	circleCollider2["bouncing"] = 0.2;
	circleCollider2["sensor"] = false;

	json circleRigidBody2;
	circleRigidBody2["name"] = "Rigidbody";
	circleRigidBody2["type"] = sfge::ComponentType::BODY2D;
	circleRigidBody2["body_type"] = p2BodyType::DYNAMIC;
	circleRigidBody2["mass"] = 1;

	circleEntity2["components"] = { circleTransform2, circleShape2, circleRigidBody2, circleCollider2 };


	json circleEntity3;
	circleEntity3["name"] = "DynamicCircle3";

	json circleTransform3;
	circleTransform3["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform3["position"] = {500, 200 };
	circleTransform3["scale"] = { 1.0,1.0 };
	circleTransform3["angle"] = 0.0;

	json circleShape3;
	circleShape3["name"] = "Circle Shape Component";
	circleShape3["type"] = sfge::ComponentType::SHAPE2D;
	circleShape3["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape3["radius"] = 30;

	json circleCollider3;
	circleCollider3["name"] = "Circle Collider";
	circleCollider3["type"] = sfge::ComponentType::COLLIDER2D;
	circleCollider3["collider_type"] = sfge::ColliderType::CIRCLE;
	circleCollider3["radius"] = 30;
	circleCollider3["bouncing"] = 0.5;
	circleCollider3["sensor"] = false;

	json circleRigidBody3;
	circleRigidBody3["name"] = "Rigidbody";
	circleRigidBody3["type"] = sfge::ComponentType::BODY2D;
	circleRigidBody3["body_type"] = p2BodyType::DYNAMIC;
	circleRigidBody3["mass"] = 1;

	circleEntity3["components"] = { circleTransform3, circleShape3, circleRigidBody3, circleCollider3 };

	json circleEntity4;
	circleEntity4["name"] = "DynamicCircle4";

	json circleTransform4;
	circleTransform4["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform4["position"] = { 600, 200 };
	circleTransform4["scale"] = { 1.0,1.0 };
	circleTransform4["angle"] = 0.0;

	json circleShape4;
	circleShape4["name"] = "Circle Shape Component";
	circleShape4["type"] = sfge::ComponentType::SHAPE2D;
	circleShape4["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape4["radius"] = 30;

	json circleCollider4;
	circleCollider4["name"] = "Circle Collider";
	circleCollider4["type"] = sfge::ComponentType::COLLIDER2D;
	circleCollider4["collider_type"] = sfge::ColliderType::CIRCLE;
	circleCollider4["radius"] = 30;
	circleCollider4["bouncing"] = 1;
	circleCollider4["sensor"] = false;

	json circleRigidBody4;
	circleRigidBody4["name"] = "Rigidbody";
	circleRigidBody4["type"] = sfge::ComponentType::BODY2D;
	circleRigidBody4["body_type"] = p2BodyType::DYNAMIC;
	circleRigidBody4["mass"] = 1;

	circleEntity4["components"] = { circleTransform4, circleShape4, circleRigidBody4, circleCollider4 };


	sceneJson["entities"] = { groundEntity, circleEntity,circleEntity2, circleEntity3, circleEntity4 };
	json contactDebugSystem = {
		{ "script_path", "scripts/contact_debug_system.py" }
	};
	json raycastDebugJson =
	{
		{ "script_path",
		//"scripts/mouse_raycast_system.py" 
		"nothing"
	}
	};
	json systemAABB = {
		{"systemClassName", "aabbSystem"}

	};

	sceneJson["systems"] = json::array({ contactDebugSystem, systemAABB});
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}
