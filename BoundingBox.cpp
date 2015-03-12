#include "BoundingBox.h"

using namespace DirectX;

BoundingBox::BoundingBox()
{
	this->position = XMFLOAT2(0, 0);
	this->size = XMFLOAT2(0, 0);
}

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



bool BoundingBox::IsObjectIntersecting(const Object& object)
{
	for (int i = 0; i < object.faces.size(); i++)
	{
		if (IsTriangleIntersecting(object.faces[i], object.worldTransform))
		{
			return true;
		}
	}
	return false;
}

bool BoundingBox::IsObjectWithin(const Object& object)
{
	for (int i = 0; i < object.faces.size(); i++)
	{
		if (!IsTriangleWithin(object.faces[i], object.worldTransform))
		{
			return false;
		}
	}
	return true;
}

bool BoundingBox::IsTriangleIntersecting(const Triangle& triangle, const DirectX::XMFLOAT4X4& worldTransform)
{
	for (int i = 0; i < 3; i++)
	{
		if (IsPointWithin(triangle.vertices[i], worldTransform))
		{
			return true;
		}
	}
	return false;
}

bool BoundingBox::IsTriangleWithin(const Triangle& triangle, const DirectX::XMFLOAT4X4& worldTransform)
{
	for (int i = 0; i < 3; i++)
	{
		if (!IsPointWithin(triangle.vertices[i], worldTransform))
		{
			return false;
		}
	}
	return true;
}

bool BoundingBox::IsPointWithin(const XMFLOAT3& point, const DirectX::XMFLOAT4X4& worldTransform)
{
	XMMATRIX tempMatrix = XMLoadFloat4x4(&worldTransform);
	XMVECTOR tempPoint = XMLoadFloat3(&point);
	XMVECTOR transformedPoint = XMVector3Transform(tempPoint, tempMatrix);
	XMFLOAT3 result;
	XMStoreFloat3(&result, transformedPoint);

	//Ignore Y value - the up and down direction ingame
	return	position.x <= result.x && position.x + size.x >= result.x &&
			position.y <= result.z && position.y + size.y >= result.z;
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
