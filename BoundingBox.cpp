#include "BoundingBox.h"

using namespace DirectX;

BoundingBox::BoundingBox(XMFLOAT2 position, XMFLOAT2 size)
{
	this->position = position;
	this->size = size;
}

BoundingBox::~BoundingBox()
{
}

XMFLOAT2 BoundingBox::GetPosition()
{
	return position;
}

XMFLOAT2 BoundingBox::GetSize()
{
	return size;
}

bool BoundingBox::IsObjectIntersecting(Object object)
{
	for (int i = 0; i < object.faces.size(); i++)
	{
		if (IsTriangleIntersecting(object.faces[i]))
		{
			return true;
		}
	}
	return false;
}

bool BoundingBox::IsTriangleIntersecting(Triangle triangle)
{
	for (int i = 0; i < 3; i++)
	{
		if (IsPointWithin(triangle.vertices[i]))
		{
			return true;
		}
	}
	return false;
}

bool BoundingBox::IsPointWithin(XMFLOAT3 point)
{
	//Ignore Y value
	return	position.x < point.x && position.x + size.x > point.x &&
			position.y < point.z && position.y + size.y > point.z;
}

BoundingBox BoundingBox::GetChildBoundingBox(int childQuadrant)
{
	XMFLOAT2 childPosition;
	XMFLOAT2 childSize = XMFLOAT2(size.x/2, size.y/2);

	switch (childQuadrant)
	{
	case 0:
		childPosition = XMFLOAT2(position.x + size.x / 2,	position.y + size.y / 2);
		break;
	case 1:
		childPosition = XMFLOAT2(position.x,				position.y + size.y / 2);
		break;
	case 2:
		childPosition = XMFLOAT2(position.x,				position.y);
		break;
	case 3:
		childPosition = XMFLOAT2(position.x + size.x / 2,	position.y);
		break;
	default:
		break;
	}

	return BoundingBox(position, size);
}
