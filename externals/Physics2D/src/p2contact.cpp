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

#include <p2contact.h>

p2Collider * p2Contact::GetColliderA() 
{
	return this->colliderA;
}

p2Collider * p2Contact::GetColliderB() 
{
	return this->colliderB;
}

void p2ContactManager::Init(p2ContactListener* contactListener){
	contacts.resize(100);
	this->contactListener = contactListener;

}

void p2Contact::Init(p2Body* bodyA, p2Body* bodyB) {
	this->colliderA = bodyA->FindCollider(0);
	this->colliderB = bodyB->FindCollider(0);

	this->SetContactPoint(bodyA, bodyB);
}

void p2Contact::SetContactPoint(p2Body* bodyA, p2Body* bodyB) {
	float radius = 0;
	p2Vec2 size = p2Vec2(0,0);
	if(bodyA->GetAABB_Ref()->type == p2ColliderType::CIRCLE) {
		radius = bodyA->GetAABB_Ref()->radius;
	}else {
		size = bodyA->GetAABB_Ref()->size;
	}

	p2Vec2 contactPoint = (bodyB->GetPosition()-bodyA->GetPosition()).Normalized()*radius;
	
	this->contactPoint = contactPoint;
}




void p2ContactManager::CheckContactBetweenBodies(std::vector<p2Body>& bodies, int bodiesSize, float dt) {
	for (int b = 0; b < bodiesSize; b++) {
		p2ColliderType colliderType = bodies[b].FindCollider(0)->colliderType;

		for (int i = b+1; i < bodiesSize; i++) {
			p2Body* otherBody = &bodies[i];
			p2AABB* otherAABB = otherBody->GetAABB_Ref();

			if (otherBody->GetType() == p2BodyType::DYNAMIC || otherBody->GetType() == p2BodyType::STATIC) {
				if (otherBody->uniqueID != bodies[b].uniqueID) {
					if (bodies[b].GetAABB_Ref()->AABBOverlapDetection(otherAABB, colliderType)) {

						//"Bounce" (teleport)
						otherBody->SetPosition(otherBody[b].GetPosition() - otherBody[b].GetLinearVelocity() * dt);
						bodies[b].SetPosition(bodies[b].GetPosition() - bodies[b].GetLinearVelocity() * dt);

						//Stop velocity
						bodies[b].SetLinearVelocity(p2Vec2(0, 0));
						otherBody->SetLinearVelocity(p2Vec2(0, 0));

						p2Contact contact = p2Contact();
						contact.Init(&bodies[b], otherBody);

						bool check = false;

						for(p2Contact c : contacts) {
							if(p2Contact::CheckIfEqual(c, contact)) {
								check = true;
								break;
							}

						}

						if (!check) {
							contacts.push_back(contact);
							contactListener->BeginContact(&contact);
						}

					}
					else {
						p2Contact contact = p2Contact();
						contact.Init(&bodies[b], otherBody);

						bool check = false;

						for (int i = 0; i < contacts.size(); i++) {
							if (p2Contact::CheckIfEqual(contacts[i], contact)) {
								check = true;
								contacts.erase(contacts.begin()+i);
								break;
							}

						}

						if (check) {
							contactListener->EndContact(&contact);
						}
					}
				}
			}
		}
	}
}

bool p2Contact::CheckIfEqual(p2Contact contactA, p2Contact contactB) {
	return (contactA.GetColliderA() == contactB.GetColliderA() && contactA.GetColliderB() == contactB.GetColliderB()) ||
			(contactA.GetColliderA() == contactB.GetColliderB() && contactA.GetColliderB() == contactB.GetColliderA());
}


