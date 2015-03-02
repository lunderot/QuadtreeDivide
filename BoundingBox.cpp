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

bool BoundingBox::IsTriangleWithin(Triangle triangle)
{
	for (int i = 0; i < 3; i++)
	{
		if (!IsPointWithin(triangle.vertices[i]))
		{
			return false;
		}
	}
	return true;
}

bool BoundingBox::IsPointWithin(XMFLOAT3 point)
{
	return	position.x < point.x && position.x + size.x > point.x &&
			position.y < point.y && position.y + size.y > point.y;
}
