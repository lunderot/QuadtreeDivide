#include "Triangle.h"


Triangle::Triangle(DirectX::XMFLOAT3 vertices[])
{
	this->vertices[0] = vertices[0];
	this->vertices[1] = vertices[1];
	this->vertices[2] = vertices[2];
}

Triangle::Triangle(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c)
{
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
}


Triangle::~Triangle()
{
}
