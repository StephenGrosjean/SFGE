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

#ifndef SFGE_P2AABB_H
#define SFGE_P2AABB_H

#include <p2vector.h>
#include "p2collider.h"

enum class p2ColliderType;

/**
* \brief Struct representing a Axis Aligned Bounding Box
*/
struct p2AABB
{
	p2Vec2 bottomLeft;
	p2Vec2 bottomRight;
	p2Vec2 topRight;
	p2Vec2 topLeft;

	p2Vec2 size;
	float radius;
	p2Vec2 MTV;

	bool isColliding;
	p2ColliderType type;

	/**
	* \brief Calculate the center and return it
	*/
	p2Vec2 GetCenter();
	/**
	* \brief Calculate the extends and return it
	*/
	 p2Vec2 GetExtends() const;

	 void SetBottomLeft(p2Vec2 point) ;
	 void SetBottomRight(p2Vec2 point) ;
	 void SetTopLeft(p2Vec2 point) ;
	 void SetTopRight(p2Vec2 point) ;

	 void SetAABB(p2Vec2 rectSize, p2Vec2 position);
	 void SetAABB(float circleRadius, p2Vec2 position);
	 void UpdateAABB_Circle(p2Vec2 position);
	 void UpdateAABB_Box(p2Vec2 position);

	 bool AABBOverlapDetection(p2AABB* otherAABB, p2ColliderType type);
};
#endif // !SFGE_P2AABB:H
