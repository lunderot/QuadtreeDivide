#include "ObjectLoader.h"

using namespace std;
using namespace DirectX;

ObjectLoader::ObjectLoader(std::string filename)
{
	ifstream file(filename);

	if (file.good())
	{
		while (!file.eof())
		{
			string objectFilename;
			string textureFilename;
			XMFLOAT4X4 worldTransform;
			file >> objectFilename >> textureFilename;
			file	>> worldTransform.m[0][0] >> worldTransform.m[0][1] >> worldTransform.m[0][2] >> worldTransform.m[0][3]
					>> worldTransform.m[1][0] >> worldTransform.m[1][1] >> worldTransform.m[1][2] >> worldTransform.m[1][3]
					>> worldTransform.m[2][0] >> worldTransform.m[2][1] >> worldTransform.m[2][2] >> worldTransform.m[2][3]
					>> worldTransform.m[3][0] >> worldTransform.m[3][1] >> worldTransform.m[3][2] >> worldTransform.m[3][3];
			objects.push_back(new Object(objectFilename, textureFilename, worldTransform));
		}
	}
	file.close();
}


ObjectLoader::~ObjectLoader()
{
	for (vector<Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
	{
		delete *i;
	}
}


Object* ObjectLoader::GetAt(int index)
{
	return objects.at(index);
}

int ObjectLoader::GetSize()
{
	return objects.size();
}
