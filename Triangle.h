#pragma once
#include <DirectXMath.h>

class Triangle
{
public:
	Triangle(DirectX::XMFLOAT3 vertices[]);
	Triangle(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c);
	~Triangle();

	DirectX::XMFLOAT3 vertices[3];
};

