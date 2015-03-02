#pragma once
#include <DirectXMath.h>

#include "Triangle.h"

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
	bool IsTriangleWithin(Triangle triangle);
	bool IsPointWithin(DirectX::XMFLOAT3 point);
};

