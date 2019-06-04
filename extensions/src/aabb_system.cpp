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

#include <extensions/aabb_system.h>
#include <engine/engine.h>
#include <engine/config.h>
#include <graphics/graphics2d.h>
#include <physics/body2d.h>
#include <physics/physics2d.h>



namespace sfge::ext
{

	AABBSystem::AABBSystem(Engine& engine) :
		System(engine)

	{
	}

	void AABBSystem::OnEngineInit()
	{
		m_Transform2DManager = m_Engine.GetTransform2dManager();
		m_Body2DManager = m_Engine.GetPhysicsManager()->GetBodyManager();
		m_TextureManager = m_Engine.GetGraphics2dManager()->GetTextureManager();
		m_Graphics2DManager = m_Engine.GetGraphics2dManager();
		m_SpriteManager = m_Engine.GetGraphics2dManager()->GetSpriteManager();
		m_Physics2dManager = m_Engine.GetPhysicsManager();
		


		auto config = m_Engine.GetConfig();
		fixedDeltaTime = config->fixedDeltaTime;
		screenSize = sf::Vector2f(config->screenResolution.x, config->screenResolution.y);


	}

	void AABBSystem::OnUpdate(float dt)
	{
		(void)dt;
	}


	void AABBSystem::OnFixedUpdate()
	{
		//rmt_ScopedCPUSample(AabbTestFixedUpdate, 0);
	}

	void AABBSystem::OnDraw()
	{
	Physics2dManager* m_Physics = m_Engine.GetPhysicsManager();
		std::vector<p2AABB*> aabbs = m_Physics->GetAABB();

		for (int i = 0; i < aabbs.size(); i++) {
			sf::Color rdmnColor(rand() % 256, rand() % 256, rand() % 256);
			sf::Color color;
			color = sf::Color(255, 0, 0);

			m_Graphics2DManager->DrawLine(meter2pixel(aabbs[i]->topRight), meter2pixel(aabbs[i]->topLeft), color);
			m_Graphics2DManager->DrawLine(meter2pixel(aabbs[i]->bottomRight), meter2pixel(aabbs[i]->bottomLeft), color);
			m_Graphics2DManager->DrawLine(meter2pixel(aabbs[i]->topLeft), meter2pixel(aabbs[i]->bottomLeft), color);
			m_Graphics2DManager->DrawLine(meter2pixel(aabbs[i]->topRight), meter2pixel(aabbs[i]->bottomRight), color);
		
		}
		std::vector<p2Contact> contacts = m_Physics2dManager->Getp2World()->GetContactManager()->contacts;
		
		for (p2Contact contact : contacts) {
			if (contact.GetColliderA() != nullptr) {
				p2Vec2 position = contact.GetColliderB()->body->GetPosition();
				p2Vec2 contactPosition = contact.contactPoint + position;
				p2Vec2 MTV_B = contact.GetColliderB()->body->GetAABB_Ref()->MTV.Normalized()/100;
				p2Vec2 MTV_A = contact.GetColliderA()->body->GetAABB_Ref()->MTV.Normalized()/100;
				float crossSize = 0.1;
				//m_Graphics2DManager->DrawVector(meter2pixel(forcePosition + contact.GetColliderB()->body->GetPosition(), meter2pixel(contactPosition), ), sf::Color::Red);
				m_Graphics2DManager->DrawVector(meter2pixel(MTV_A), meter2pixel(contactPosition));
				m_Graphics2DManager->DrawVector(meter2pixel(MTV_B), meter2pixel(contactPosition));

				m_Graphics2DManager->DrawLine(meter2pixel(contactPosition), meter2pixel(contactPosition + p2Vec2(crossSize, crossSize)), sf::Color::White);
				m_Graphics2DManager->DrawLine(meter2pixel(contactPosition), meter2pixel(contactPosition + p2Vec2(-crossSize, crossSize)), sf::Color::White);
				m_Graphics2DManager->DrawLine(meter2pixel(contactPosition), meter2pixel(contactPosition + p2Vec2(crossSize, -crossSize)), sf::Color::White);
				m_Graphics2DManager->DrawLine(meter2pixel(contactPosition), meter2pixel(contactPosition + p2Vec2(-crossSize, -crossSize)), sf::Color::White);
				
			}
		}


		//DRAW QUAD
		/*p2World* m_world = m_Physics2dManager->Getp2World();
		p2QuadTree* quadTree = m_world->GetQuadTree();
		p2AABB* quadBounds = quadTree->GetBounds();


		m_Graphics2DManager->DrawLine(meter2pixel(quadBounds->topRight), meter2pixel(quadBounds->topLeft));
		m_Graphics2DManager->DrawLine(meter2pixel(quadBounds->bottomRight), meter2pixel(quadBounds->bottomLeft));
		m_Graphics2DManager->DrawLine(meter2pixel(quadBounds->topLeft), meter2pixel(quadBounds->bottomLeft));
		m_Graphics2DManager->DrawLine(meter2pixel(quadBounds->topRight), meter2pixel(quadBounds->bottomRight));
	


		std::vector<p2QuadTree*> quads;
		for(int i = 0; i < 3; i++) {
			quads.push_back(quadTree->GetNode(i));
		}

		for (int i = 0; i < quads.size() - 1; i++) {
			p2AABB* currentTreeBounds = quads[i]->GetBounds();
			m_Graphics2DManager->DrawLine(meter2pixel(currentTreeBounds->topRight), meter2pixel(currentTreeBounds->topLeft), sf::Color::Green);
			m_Graphics2DManager->DrawLine(meter2pixel(currentTreeBounds->bottomRight), meter2pixel(currentTreeBounds->bottomLeft), sf::Color::Green);
			m_Graphics2DManager->DrawLine(meter2pixel(currentTreeBounds->topLeft), meter2pixel(currentTreeBounds->bottomLeft), sf::Color::Green);
			m_Graphics2DManager->DrawLine(meter2pixel(currentTreeBounds->topRight), meter2pixel(currentTreeBounds->bottomRight), sf::Color::Green);
		}*/
		

	}

}
