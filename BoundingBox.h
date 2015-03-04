#pragma once
#include <DirectXMath.h>

#include "Triangle.h"
#include "Object.h"

class BoundingBox
{
private:
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 size;
public:
	BoundingBox(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size);
	~BoundingBox();

	DirectX::XMFLOAT2 GetPosition();
	DirectX::XMFLOAT2 GetSize();

	bool IsObjectIntersecting(Object object);
	bool IsTriangleIntersecting(Triangle triangle);
	bool IsPointWithin(DirectX::XMFLOAT3 point);

	BoundingBox GetChildBoundingBox(int childQuadrant);
};

