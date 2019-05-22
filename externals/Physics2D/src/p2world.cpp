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
#include <p2world.h>
#include <iostream>


p2World::p2World(p2Vec2 gravity): m_Gravity(gravity)
{

	m_Bodies.resize(MAX_BODY_LEN);
}

void p2World::Step(float dt)
{
	for (p2Body& body : m_Bodies) {
		if (body.GetType() == p2BodyType::DYNAMIC) {
			//body.SetLinearVelocity(body.GetLinearVelocity() + m_Gravity * dt);
			body.ApplyForceToCenter(m_Gravity * dt);
			body.SetPosition(body.GetPosition() + body.GetLinearVelocity() * dt);

			//std::cout << body.GetAABB().topRight.y << std::endl;
			//std::cout << "POSY:" << body.GetPosition().y << std::endl;

			p2ColliderType colliderType = body.FindCollider(0)->colliderType;

			switch(colliderType) {
				case p2ColliderType::BOX:
					p2RectShape* boxShape = static_cast<p2RectShape*>(body.FindCollider(0)->shape);
					body.GetAABB_Ref()->UpdateAABB_Box(body.GetPosition());
				break;

				case p2ColliderType::CIRCLE:
					p2CircleShape* circleShape = static_cast<p2CircleShape*>(body.FindCollider(0)->shape);
					body.GetAABB_Ref()->UpdateAABB_Circle(body.GetPosition());
					break;
			}
			
			

		}

	}
}

p2Body * p2World::CreateBody(p2BodyDef* bodyDef)
{
	p2Body& body = m_Bodies[m_BodyIndex];
	body.Init(bodyDef);
	m_BodyIndex++;
	return &body;
}

void p2World::SetContactListener(p2ContactListener * contactListener)
{
}

std::vector<p2AABB*> p2World::GetAABB() {
	std::vector<p2AABB*> aabbs;
	aabbs.clear();

	/*for(p2Body body : m_Bodies) {
		aabbs.push_back(body.GetAABB());
	}*/
	for(int i = 0; i < m_BodyIndex; i++) {
		aabbs.push_back(m_Bodies[i].GetAABB_Ref());

	}
	return aabbs;
}


