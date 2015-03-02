#pragma once

#include <DirectXMath.h>
#include <string>
#include <vector>
#include <fstream>

#include "Triangle.h"

struct Vertex
{
	DirectX::XMFLOAT3 pos;
};

class Object
{
public:

	std::vector<DirectX::XMFLOAT3> vertices;
	std::vector<Triangle> faces;

	Object(std::string modelFilename);
	~Object();
};

