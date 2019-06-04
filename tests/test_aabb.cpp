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

TEST(System, TestAABB)
{
	sfge::Engine engine;

	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	config->gravity = p2Vec2(0, 9.81f);
	config->maxFramerate = 60;
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Test AABB";

//STATIC ENTITIES
	json groundEntity;
	groundEntity["name"] = "Ground";

	json groundTransform;
	groundTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	groundTransform["position"] = { 480,601 };
	groundTransform["scale"] = { 1.0,1.0 };
	groundTransform["angle"] = 0.0;

	json groundShape;
	groundShape["name"] = "Rect Shape Component";
	groundShape["type"] = sfge::ComponentType::SHAPE2D;
	groundShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	groundShape["size"] = { 600,100 };

	json groundRigidBody;
	groundRigidBody["name"] = "Rigidbody";
	groundRigidBody["type"] = sfge::ComponentType::BODY2D;
	groundRigidBody["body_type"] = p2BodyType::STATIC;

	json groundCollider;
	groundCollider["name"] = "Rect Collider";
	groundCollider["type"] = sfge::ComponentType::COLLIDER2D;
	groundCollider["collider_type"] = sfge::ColliderType::BOX;
	groundCollider["size"] = { 600,100 };
	groundCollider["sensor"] = false;

	groundEntity["components"] = { groundTransform, groundShape, groundRigidBody, groundCollider };


	json wallEntity;
	wallEntity["name"] = "Wall";

	json wallTransform;
	wallTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	wallTransform["position"] = { 750,450 };
	wallTransform["scale"] = { 1.0,1.0 };
	wallTransform["angle"] = 0.0;

	json wallShape;
	wallShape["name"] = "Rect Shape Component";
	wallShape["type"] = sfge::ComponentType::SHAPE2D;
	wallShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	wallShape["size"] = { 50,200 };

	json wallRigidBody;
	wallRigidBody["name"] = "Rigidbody";
	wallRigidBody["type"] = sfge::ComponentType::BODY2D;
	wallRigidBody["body_type"] = p2BodyType::STATIC;

	json wallCollider;
	wallCollider["name"] = "Rect Collider";
	wallCollider["type"] = sfge::ComponentType::COLLIDER2D;
	wallCollider["collider_type"] = sfge::ColliderType::BOX;
	wallCollider["size"] = { 50,200 };
	wallCollider["sensor"] = false;

	wallEntity["components"] = { wallTransform, wallShape, wallRigidBody, wallCollider };

	json wallEntity2;
	wallEntity2["name"] = "Wall2";

	json wallTransform2;
	wallTransform2["type"] = sfge::ComponentType::TRANSFORM2D;
	wallTransform2["position"] = { 200,450 };
	wallTransform2["scale"] = { 1.0,1.0 };
	wallTransform2["angle"] = 0.0;

	json wallShape2;
	wallShape2["name"] = "Rect Shape Component";
	wallShape2["type"] = sfge::ComponentType::SHAPE2D;
	wallShape2["shape_type"] = sfge::ShapeType::RECTANGLE;
	wallShape2["size"] = { 50,200 };

	json wallRigidBody2;
	wallRigidBody2["name"] = "Rigidbody";
	wallRigidBody2["type"] = sfge::ComponentType::BODY2D;
	wallRigidBody2["body_type"] = p2BodyType::STATIC;

	json wallCollider2;
	wallCollider2["name"] = "Rect Collider";
	wallCollider2["type"] = sfge::ComponentType::COLLIDER2D;
	wallCollider2["collider_type"] = sfge::ColliderType::BOX;
	wallCollider2["size"] = { 50,200 };
	wallCollider2["sensor"] = false;

	wallEntity2["components"] = { wallTransform2, wallShape2, wallRigidBody2, wallCollider2};
//END STATIC ENTITIES

//DYNAMIC ENTITIES
	json circleEntity;
	circleEntity["name"] = "DynamicCircle";

	json circleTransform;
	circleTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform["position"] = { 500,500 };
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
	circleCollider["bouncing"] = 0.5;
	circleCollider["sensor"] = false;

	json circleRigidBody;
	circleRigidBody["name"] = "Rigidbody";
	circleRigidBody["type"] = sfge::ComponentType::BODY2D;
	circleRigidBody["body_type"] = p2BodyType::DYNAMIC;
	circleRigidBody["mass"] = 1;

	circleEntity["components"] = { circleTransform, circleShape, circleRigidBody, circleCollider };

	json circleEntity2;
	circleEntity2["name"] = "DynamicCircle";

	json circleTransform2;
	circleTransform2["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform2["position"] = { 400, 500 };
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
	circleCollider2["bouncing"] = 0.5;
	circleCollider2["sensor"] = false;

	json circleRigidBody2;
	circleRigidBody2["name"] = "Rigidbody";
	circleRigidBody2["type"] = sfge::ComponentType::BODY2D;
	circleRigidBody2["body_type"] = p2BodyType::DYNAMIC;
	circleRigidBody2["mass"] = 1;

	circleEntity2["components"] = { circleTransform2, circleShape2, circleRigidBody2, circleCollider2 };

	sceneJson["entities"] = { groundEntity, circleEntity,circleEntity2, wallEntity, wallEntity2 };
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
