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
}

void p2Contact::SetContactPoint(p2Body* bodyA, p2Body* bodyB) {
	float radius = 0;
	p2Vec2 size = p2Vec2(0,0);
	p2Vec2 contactPoint = p2Vec2();

	//Circle and Circle
	if(bodyA->GetAABB_Ref()->type == p2ColliderType::CIRCLE 
		&& bodyB->GetAABB_Ref()->type == p2ColliderType::CIRCLE) 
	{
		radius = bodyB->GetAABB_Ref()->radius;
		contactPoint = (bodyA->GetPosition() - bodyB->GetPosition()).Normalized()*radius;
	}
	else if (bodyA->GetAABB_Ref()->type == p2ColliderType::BOX
		&& bodyB->GetAABB_Ref()->type == p2ColliderType::CIRCLE)
	{
		radius = bodyB->GetAABB_Ref()->radius;
		size = bodyA->GetAABB_Ref()->size;

		if(this->topContact) {
			contactPoint = p2Vec2(0,radius);
		}else if(this->bottomContact) {
			contactPoint = p2Vec2(0, -radius);
		}else if(this->leftContact) {
			contactPoint = p2Vec2(radius, 0);
		}else if(this->rightContact) {
			contactPoint = p2Vec2(-radius, 0);
		}else {
			contactPoint = p2Vec2();
		}
	}
	else if (bodyA->GetAABB_Ref()->type == p2ColliderType::CIRCLE
		&& bodyB->GetAABB_Ref()->type == p2ColliderType::BOX)
	{
		radius = bodyA->GetAABB_Ref()->radius;
		size = bodyB->GetAABB_Ref()->size;

		if (this->topContact) {
			contactPoint = p2Vec2(0, -radius);
		}
		else if (this->bottomContact) {
			contactPoint = p2Vec2(0, radius);
		}
		else if (this->leftContact) {
			contactPoint = p2Vec2(radius, 0);
		}
		else if (this->rightContact) {
			contactPoint = p2Vec2(-radius, 0);
		}
		else {
			contactPoint = p2Vec2();
		}
	}

	
	this->contactPoint = contactPoint;
}


p2Vec2 p2Contact::GetContactPoint() {
	return this->contactPoint;
}

void p2ContactManager::CheckContactBetweenBodies(std::vector<p2Body>& bodies, int bodiesSize, float dt, p2Vec2 m_Gravity) {
	for (int b = 0; b < bodiesSize; b++) {
		p2ColliderType colliderType = bodies[b].FindCollider(0)->colliderType;

		for (int i = b+1; i < bodiesSize; i++) {
			p2Body* bodyA = &bodies[i];
			p2AABB* otherAABB = bodyA->GetAABB_Ref();

			p2Body* bodyB = &bodies[b];

			if (bodyA->GetType() == p2BodyType::DYNAMIC || bodyA->GetType() == p2BodyType::STATIC) {
				if (bodyA->uniqueID != bodyB->uniqueID) {
					if (bodyB->GetAABB_Ref()->AABBOverlapDetection(otherAABB, colliderType) || bodyA->GetAABB_Ref()->AABBOverlapDetection(bodyB->GetAABB_Ref(),colliderType)) {

						p2Contact contact = p2Contact();
						contact.Init(bodyB, bodyA);

						bool check = false;

						for(p2Contact c : contacts) {
							if(p2Contact::CheckIfEqual(c, contact)) {
								check = true;
								break;
							}

						}

						

						float radius;
						//Collision
						//p2Vec2 normalVector = (contact.contactPoint + bodyB->GetPosition()) - bodyA->GetPosition();
						p2Vec2 MTV = p2Vec2();

						//Circle and Circle
						if(bodyA->FindCollider(0)->colliderType == p2ColliderType::CIRCLE 
							&& bodyB->FindCollider(0)->colliderType == p2ColliderType::CIRCLE) 
						{
							MTV = p2Contact::FindMTVCircleCircle(*bodyB, *bodyA);
						}
						//Circle and Box
						else if(bodyA->FindCollider(0)->colliderType == p2ColliderType::CIRCLE 
							&& bodyB->FindCollider(0)->colliderType == p2ColliderType::BOX) 
						{
							MTV = p2Contact::FindMTVCircleBox(*bodyA, *bodyB, &contact);
							float angle = p2Vec2::AngleBetween(p2Vec2(1, 0), MTV.Normalized(), 1);

							if(angle == 90) {
								contact.topContact = true;
							}else if(angle == 180) {
								contact.leftContact = true;
							}else if(angle == 270) {
								contact.bottomContact = true;
							}else if(angle == 360  || angle == 0) {
								contact.rightContact = true;
							}	
						}
						//Box and Circle
						else if (bodyA->FindCollider(0)->colliderType == p2ColliderType::BOX
							&& bodyB->FindCollider(0)->colliderType == p2ColliderType::CIRCLE)
						{
							MTV = p2Contact::FindMTVCircleBox(*bodyB, *bodyA, &contact);

							float angle = p2Vec2::AngleBetween(p2Vec2(1, 0), MTV.Normalized(), 1);

							if (angle == 90) {
								contact.topContact = true;
							}
							else if (angle == 180) {
								contact.leftContact = true;
							}
							else if (angle == 270) {
								contact.bottomContact = true;
							}
							else if (angle == 360 || angle == 0) {
								contact.rightContact = true;
							}
						}
						//Box and Box
						else if (bodyA->FindCollider(0)->colliderType == p2ColliderType::BOX
							&& bodyB->FindCollider(0)->colliderType == p2ColliderType::BOX)
						{

						}
						contact.SetContactPoint(bodyB, bodyA);

						if (!check) {
							contacts.push_back(contact);
							contactListener->BeginContact(&contact);
						}

						if(MTV.x != 0 || MTV.y != 0) {
							if (bodyA->GetType() == p2BodyType::DYNAMIC && !bodyA->FindCollider(0)->IsSensor()) {
								bodyA->SetPosition(bodyA->GetPosition() - MTV);
							}
							if (bodyB->GetType() == p2BodyType::DYNAMIC && !bodyB->FindCollider(0)->IsSensor()) {
								bodyB->SetPosition(bodyB->GetPosition() - MTV);
							}
							p2Vec2 velocityA = bodyA->GetLinearVelocity();
							p2Vec2 velocityB = bodyB->GetLinearVelocity();

							p2Vec2 reflexA = velocityA - MTV.Normalized() * p2Vec2::Dot(velocityA, MTV.Normalized())*2;
							p2Vec2 reflexB = velocityB - MTV.Normalized() * p2Vec2::Dot(velocityB, MTV.Normalized()) * 2;

							bodyA->GetAABB_Ref()->MTV = MTV * -1;
							bodyB->GetAABB_Ref()->MTV = MTV;

							if(bodyA->GetType() == p2BodyType::DYNAMIC && !bodyA->FindCollider(0)->IsSensor()) {
								bodyA->SetLinearVelocity(reflexA);

							}
							if (bodyB->GetType() == p2BodyType::DYNAMIC && !bodyB->FindCollider(0)->IsSensor()) {
								bodyB->SetLinearVelocity(reflexB);
							}
							

						}

					}
					else {
						p2Contact contact = p2Contact();
						contact.Init(&bodies[b], bodyA);
						contact.SetContactPoint(&bodies[b], bodyA);

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

p2Vec2 p2Contact::FindMTVCircleCircle(p2Body bodyA, p2Body bodyB) {
	float radiusA = bodyA.GetAABB_Ref()->radius;
	float radiusB = bodyB.GetAABB_Ref()->radius;

	p2Vec2 vectorBetweenBody = bodyA.GetPosition() - bodyB.GetPosition();

	if(vectorBetweenBody.GetMagnitude() < radiusA+radiusB) {
		p2Vec2 vectorBetweenBodyNorm = vectorBetweenBody.Normalized();
		p2Vec2 MTV = vectorBetweenBody - (vectorBetweenBodyNorm * (radiusA + radiusB));
		return MTV;
	}

	return p2Vec2();


}

p2Vec2 p2Contact::FindMTVCircleBox(p2Body circleBody, p2Body boxBody, p2Contact* contact) {
	float radiusCircle = circleBody.GetAABB_Ref()->radius;
	p2Vec2 circlePosition = circleBody.GetPosition();
	p2Vec2 boxPosition = boxBody.GetPosition();
	p2Vec2 sizeBox = boxBody.GetAABB_Ref()->size;
	p2AABB boxAABB = boxBody.GetAABB();

	p2Vec2 closestAngle = p2Vec2();
	float closestDistance = 5000;
	std::vector<p2Vec2> boxAngles;
	boxAngles.push_back(boxAABB.topLeft);
	boxAngles.push_back(boxAABB.topRight);
	boxAngles.push_back(boxAABB.bottomLeft);
	boxAngles.push_back(boxAABB.bottomRight);

	for (int i = 0; i != 3; i++) {
		float distance = p2Vec2::DistanceBetween(boxAngles[i], circlePosition);
		if (distance < closestDistance) {
			closestAngle = boxAngles[i];
			closestDistance = distance;
		}
	}


	p2Vec2 closestAngleVector = closestAngle - circlePosition;

	//Check which axis
	if((circlePosition.y+radiusCircle <= boxPosition.y+sizeBox.y || circlePosition.y >= boxPosition.y-sizeBox.y) 
		&& (circlePosition.x >= boxPosition.x - sizeBox.x || circlePosition.x <= boxPosition.x + sizeBox.x)
		/*&& (radiusCircle > closestAngleVector.GetMagnitude())*/){

		p2Vec2 vectorBetweenBody = circlePosition - boxPosition;

		p2Vec2 vectorBetweenBody_x =  p2Vec2(vectorBetweenBody.x,0);
		p2Vec2 vectorBetweenBody_y = p2Vec2(0, vectorBetweenBody.y);


		p2Vec2 vectorBetweenBodyNorm_x = vectorBetweenBody_x.Normalized();
		p2Vec2 vectorBetweenBodyNorm_y = vectorBetweenBody_y.Normalized();


		p2Vec2 MTVx = vectorBetweenBody_x - (vectorBetweenBodyNorm_x * (radiusCircle + sizeBox.x));
		p2Vec2 MTVy = vectorBetweenBody_y - (vectorBetweenBodyNorm_y * (radiusCircle + sizeBox.y));

		if(MTVx.GetMagnitude() < MTVy.GetMagnitude()) {
			return MTVx;
		}else {
			return MTVy;
		}

	}

	return p2Vec2();



}

p2Vec2 p2Contact::FindMTVBoxBox(p2Body bodyA, p2Body bodyB) {
	
	return p2Vec2();
}



