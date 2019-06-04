#include "..\include\p2quadtree.h"




p2QuadTree::p2QuadTree() {

}


p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds)
{
	m_NodeLevel = nodeLevel;
	m_Bounds = bounds;


}

p2QuadTree::~p2QuadTree()
{
}

void p2QuadTree::Clear()
{
}

void p2QuadTree::Split()
{

	p2AABB newAABB;
	for(int i = 0; i < CHILD_TREE_NMB; i++) {
		nodes[i]->m_NodeLevel = m_NodeLevel + 1;
		nodes[i]->m_Parent = this;
	}

	//Top Left AABB
	newAABB.SetTopLeft(this->m_Bounds.topLeft);
	newAABB.SetTopRight(p2Vec2(this->m_Bounds.topRight.x / 2, this->m_Bounds.topRight.y));
	newAABB.SetBottomLeft(p2Vec2(this->m_Bounds.bottomLeft.x, this->m_Bounds.bottomLeft.y / 2));
	newAABB.SetBottomRight(p2Vec2(this->m_Bounds.bottomRight.x/2, this->m_Bounds.bottomRight.y / 2));

	nodes[0]->m_Bounds = newAABB;

	//Top Right AABB
	newAABB.SetTopLeft(p2Vec2(this->m_Bounds.topRight.x/2, this->m_Bounds.topRight.y));
	newAABB.SetTopRight(this->m_Bounds.topRight);
	newAABB.SetBottomLeft(p2Vec2(this->m_Bounds.bottomRight.x / 2, this->m_Bounds.bottomRight.y / 2));
	newAABB.SetBottomRight(p2Vec2(this->m_Bounds.bottomRight.x, this->m_Bounds.bottomRight.y/2));

	nodes[1]->m_Bounds = newAABB;

	//Bottom Left AABB
	newAABB.SetTopLeft(p2Vec2(this->m_Bounds.topLeft.x, this->m_Bounds.topLeft.y/2));
	newAABB.SetTopRight(p2Vec2(this->m_Bounds.topRight.x/2, this->m_Bounds.topRight.y/2));
	newAABB.SetBottomLeft(this->m_Bounds.bottomLeft);
	newAABB.SetBottomRight(p2Vec2(this->m_Bounds.bottomRight.x/2, this->m_Bounds.bottomRight.y));

	nodes[2]->m_Bounds = newAABB;

	//Bottom Right AABB
	newAABB.SetTopLeft(p2Vec2(this->m_Bounds.topLeft.x/2, this->m_Bounds.topLeft.y/2));
	newAABB.SetTopRight(p2Vec2(this->m_Bounds.topRight.x, this->m_Bounds.topRight.y/2));
	newAABB.SetBottomLeft(p2Vec2(this->m_Bounds.bottomLeft.x/2, this->m_Bounds.bottomLeft.y));
	newAABB.SetBottomRight(this->m_Bounds.bottomRight);

	nodes[3]->m_Bounds = newAABB;

	this->nodes[0] = nodes[0];
	this->nodes[1] = nodes[1];
	this->nodes[2] = nodes[2];
	this->nodes[3] = nodes[3];
}

int p2QuadTree::GetIndex(p2Body * rect)
{
	return 0;
}

void p2QuadTree::Insert(p2Body * obj)
{
}

void p2QuadTree::Retrieve()
{
}

p2AABB* p2QuadTree::GetBounds() {
	return &m_Bounds;
}

p2QuadTree* p2QuadTree::GetNode(int index) {
	return nodes[index];
}


