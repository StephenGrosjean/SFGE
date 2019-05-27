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
	config->gravity = p2Vec2(0.0f, 9.81f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Test AABB";

	json circleBody1;
	circleBody1["name"] = "Static Circle";

	json transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 300,300 };
	transformJson1["scale"] = { 1.0,1.0 };
	transformJson1["angle"] = 0.0;

	json circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 50;

	json rigidBodyJsonDynamic;
	rigidBodyJsonDynamic["name"] = "Rigidbody";
	rigidBodyJsonDynamic["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJsonDynamic["body_type"] = p2BodyType::DYNAMIC;
	rigidBodyJsonDynamic["mass"] = 1;

	json rigidBodyJsonStatic;
	rigidBodyJsonStatic["name"] = "Rigidbody";
	rigidBodyJsonStatic["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJsonStatic["body_type"] = p2BodyType::STATIC;
	rigidBodyJsonStatic["mass"] = 1;


	json circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 50;
	circleColliderJson["bouncing"] = 0.5;
	circleColliderJson["sensor"] = true;

	circleBody1["components"] = { transformJson1, circleShapeJson, rigidBodyJsonStatic, circleColliderJson };

	json circleBody2;
	circleBody2["name"] = "DynamicCircle";

	json transformJson3;
	transformJson3["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson3["position"] = { 200,100 };
	transformJson3["scale"] = { 1.0,1.0 };
	transformJson3["angle"] = 0.0;

	json circleShapeJson3;
	circleShapeJson3["name"] = "Circle Shape Component";
	circleShapeJson3["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson3["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson3["radius"] = 60;

	json circleColliderJson3;
	circleColliderJson3["name"] = "Circle Collider";
	circleColliderJson3["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson3["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson3["radius"] = 60;
	circleColliderJson3["bouncing"] = 0.5;
	circleColliderJson3["sensor"] = true;
	circleBody2["components"] = { transformJson3, circleShapeJson3, rigidBodyJsonDynamic, circleColliderJson3 };

	sceneJson["entities"] = { circleBody1, circleBody2 };
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
