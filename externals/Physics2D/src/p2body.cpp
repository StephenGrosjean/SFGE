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
#include <p2body.h>
#include <iostream>

void p2Body::Init(p2BodyDef* bodyDef)
{
	//Setting the p2Body variables
	type = bodyDef->type;
	position = bodyDef->position;
	linearVelocity = bodyDef->linearVelocity;
	aabb = bodyDef->aabb;
	gravityScale = bodyDef->gravityScale;
	mass = bodyDef->mass;

	bodyDef->uniqueID = rand() %4096;
	uniqueID = bodyDef->uniqueID;

	//Resizing collider array
	m_Colliders.resize(MAX_COLLIDER_LEN);

}

p2Vec2 p2Body::GetLinearVelocity() const
{
	return linearVelocity;
}

void p2Body::SetLinearVelocity(p2Vec2 velocity)
{
	linearVelocity = velocity;
}

float p2Body::GetAngularVelocity()
{
	return angularVelocity;
}

p2Vec2 p2Body::GetPosition()
{
	return position;
}

void p2Body::SetPosition(p2Vec2 position)
{
	this->position = position;
}

p2Collider * p2Body::CreateCollider(p2ColliderDef * colliderDef)
{
	p2Collider& collider = m_Colliders[m_ColliderIndex];
	m_ColliderIndex++;
	collider.Init(colliderDef, this);
	p2ColliderType colliderType = collider.colliderType;
	p2Vec2 BL, TR;

	switch (colliderType) {
		p2RectShape* boxShape;
		p2CircleShape* circleShape;

		case p2ColliderType::BOX:
			boxShape = static_cast<p2RectShape*>(collider.shape);
			if (!this->aabbDefined) {
				this->aabb.SetAABB(boxShape->GetSize(), position);
				this->aabbDefined = true;
				this->aabb.type = colliderType;
				std::cout << "Rectangle position: " << position.x << " , " << position.y << std::endl;
				std::cout << "Rectangle aabb: " << aabb.GetExtends().x << " , " << aabb.GetExtends().y << std::endl;
			}
			break;

		case p2ColliderType::CIRCLE:
			circleShape = static_cast<p2CircleShape*>(collider.shape);
			if (!this->aabbDefined) {
				this->aabb.SetAABB(circleShape->GetRadius(), position);
				std::cout << "Circle position: " << position.x << " , " << position.y << std::endl;
				std::cout << "Circle aabb: " << aabb.GetExtends().x << " , " << aabb.GetExtends().y << std::endl;
				this->aabbDefined = true;
				this->aabb.type = colliderType;

			}
			break;
	}
	std::cout << "Finished Collider Creation" << std::endl;
	return &collider;
}

void p2Body::ApplyForceToCenter(const p2Vec2& force)
{
	if (mass < 1) {
		mass = 1;
	}
	
	linearVelocity += force/mass;
	
}

p2BodyType p2Body::GetType() const
{
	return type;
	//return p2BodyType::STATIC;
}

float p2Body::GetMass() const
{
	return this->mass;
}

p2Collider* p2Body::FindCollider(int colliderIndex) {
	return &m_Colliders[colliderIndex];
}

p2AABB* p2Body::GetAABB_Ref() {
	return &aabb;
}

p2AABB p2Body::GetAABB() {
	return aabb;
}