#include "..\include\p2collider.h"

void p2Collider::Init(p2ColliderDef* colliderDef) {
	userData = colliderDef->userData;
	shape = colliderDef->shape;
	colliderType = colliderDef->colliderType;
	restitution = colliderDef->restitution;
	isSensor = colliderDef->isSensor;

}

bool p2Collider::IsSensor()
{
	return this->isSensor;
}

void * p2Collider::GetUserData()
{
	return userData;
}

void p2Collider::SetUserData(void* colliderData)
{
	userData = colliderData;
}