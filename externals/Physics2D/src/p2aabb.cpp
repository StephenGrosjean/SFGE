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

#include <p2aabb.h>
#include <iostream>
#include "p2collider.h"

p2Vec2 p2AABB::GetCenter()
{
	 return (topRight - bottomLeft) / 2;
}

p2Vec2 p2AABB::GetExtends() const
{
	return { bottomLeft.x + topRight.x, bottomLeft.y + topRight.y };
}

void p2AABB::SetBottomLeft(p2Vec2 point) {
	this->bottomLeft = point;
}

void p2AABB::SetBottomRight(p2Vec2 point) {

	this->bottomRight = point;
}

void p2AABB::SetTopLeft(p2Vec2 point) {
	this->topLeft = point;
}

void p2AABB::SetTopRight(p2Vec2 point)  {
	this->topRight = point;
}




void p2AABB::UpdateAABB_Circle(p2Vec2 position) {
	p2Vec2 BL = p2Vec2(-radius, radius);
	p2Vec2 BR = p2Vec2(radius, radius);
	p2Vec2 TR = p2Vec2(radius, -radius);
	p2Vec2 TL = p2Vec2(-radius, -radius);

	this->SetTopRight(position + TR);
	this->SetBottomLeft(position + BL);
	this->SetBottomRight(position + BR);
	this->SetTopLeft(position + TL);
}
void p2AABB::UpdateAABB_Box(p2Vec2 position) {
	p2Vec2 BL = p2Vec2(-size.x, size.y);
	p2Vec2 BR = p2Vec2(size.x, size.y);
	p2Vec2 TR = p2Vec2(size.x, -size.y);
	p2Vec2 TL = p2Vec2(-size.x, -size.y);

	this->SetTopRight(position + TR);
	this->SetBottomLeft(position + BL);
	this->SetBottomRight(position + BR);
	this->SetTopLeft(position + TL);
}

void p2AABB::SetAABB(p2Vec2 rectSize, p2Vec2 position){
	p2Vec2 BL = p2Vec2(-rectSize.x, rectSize.y);
	p2Vec2 BR = p2Vec2(rectSize.x, rectSize.y);
	p2Vec2 TR = p2Vec2(rectSize.x, -rectSize.y);
	p2Vec2 TL = p2Vec2(-rectSize.x, -rectSize.y);

	this->SetTopRight(position + TR);
	this->SetBottomLeft(position + BL);
	this->SetBottomRight(position + BR);
	this->SetTopLeft(position + TL);

	this->size = rectSize;
	//std::cout << "Creating AABB : " << topRight.x << " , " << topRight.y << std::endl;


}
void p2AABB::SetAABB(float circleSize, p2Vec2 position) {
//	std::cout << "SET AABB : position-> " << position.x << " , " << position.y << "size-> " << circleSize  <<std::endl;

	p2Vec2 BL = p2Vec2(-circleSize, circleSize);
	p2Vec2 BR = p2Vec2(circleSize, circleSize);
	p2Vec2 TR = p2Vec2(circleSize, -circleSize);
	p2Vec2 TL = p2Vec2(-circleSize, -circleSize);

	this->SetTopRight(position + TR);
	this->SetBottomLeft(position + BL);
	this->SetBottomRight(position + BR);
	this->SetTopLeft(position + TL);

	this->radius = circleSize;
}

bool p2AABB::CollisionDetection(p2AABB* otherAABB, p2ColliderType type) {
	bool isCollision = false;
	p2Vec2 currentPoint = this->bottomLeft;

	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			currentPoint = this->bottomLeft;
			break;

		case 1:
			currentPoint = this->bottomRight;
			break;

		case 2:
			currentPoint = this->topLeft;
			break;

		case 3:
			currentPoint = this->topRight;
			break;
		}
		//std::cout << "OTHER : " << otherAABB->topRight.y << std::endl;
		if ((currentPoint.x > otherAABB->topLeft.x && currentPoint.x < otherAABB->topRight.x) && (currentPoint.y < otherAABB->bottomLeft.y && currentPoint.y > otherAABB->topLeft.y)) {
			isCollision = true;
		}
	}

	return isCollision;
}






