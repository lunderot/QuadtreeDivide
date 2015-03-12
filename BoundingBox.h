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
	BoundingBox();
	BoundingBox(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size);
	~BoundingBox();

	DirectX::XMFLOAT2 GetPosition();
	DirectX::XMFLOAT2 GetSize();

	bool IsObjectIntersecting(const Object& object);
	bool IsObjectWithin(const Object& object);
	bool IsTriangleIntersecting(const Triangle& triangle, const DirectX::XMFLOAT4X4& worldTransform);
	bool IsTriangleWithin(const Triangle& triangle, const DirectX::XMFLOAT4X4& worldTransform);
	bool IsPointWithin(const DirectX::XMFLOAT3& point, const DirectX::XMFLOAT4X4& worldTransform);

	BoundingBox GetChildBoundingBox(int childQuadrant);
};

