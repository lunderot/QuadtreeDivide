#pragma once
#include <string>
#include <vector>
#include <DirectXMath.h>
#include "Object.h"

class ObjectLoader
{
private:
	std::vector<Object*> objects;
public:
	ObjectLoader(std::string filename);
	~ObjectLoader();
	Object* GetAt(int index);
	int GetSize();
};

