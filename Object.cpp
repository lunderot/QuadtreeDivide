#include "Object.h"

using namespace std;
using namespace DirectX;

Object::Object(string modelFilename, XMFLOAT4X4 worldTransform)
{
	this->modelFilename = modelFilename;
	this->worldTransform = worldTransform;

	bool result = true;
	ifstream file(modelFilename);

	if (file.good())
	{
		while (!file.eof())
		{
			string command;
			file >> command;
			if (command == "v")
			{
				XMFLOAT3 tempVertex;
				file >> tempVertex.x;
				file >> tempVertex.y;
				file >> tempVertex.z;
				tempVertex.z *= -1.0f;
				vertices.push_back(tempVertex);
			}
			else if (command == "f")
			{
				int vertexIndex[3];
				int uvIndex[3];
				int normalIndex[3];

				for (int i = 0; i < 3; i++)
				{
					file >> vertexIndex[i];
					//Check if we can load UV coordinates
					if (file.peek() == '/')
					{
						file.get();
						file >> uvIndex[i];
						//Check if we can load normals
						if (file.peek() == '/')
						{
							file.get();
							file >> normalIndex[i];
						}
					}
				}
				Triangle tempTriangle(vertices[vertexIndex[2] - 1], vertices[vertexIndex[1] - 1], vertices[vertexIndex[0] - 1]);
				faces.push_back(tempTriangle);
			}
		}
	}
	else
	{
		throw runtime_error("Failed to load file: " + modelFilename);
	}
	file.close();
}

Object::~Object()
{
}

std::ofstream& operator<<(std::ofstream& file, const Object& object)
{
	file << "o " << object.modelFilename << " ";
	file	<< object.worldTransform.m[0][0] << " " << object.worldTransform.m[0][1] << " " << object.worldTransform.m[0][2] << " " << object.worldTransform.m[0][3]<< " " 
			<< object.worldTransform.m[1][0] << " " << object.worldTransform.m[1][1] << " " << object.worldTransform.m[1][2] << " " << object.worldTransform.m[1][3]<< " " 
			<< object.worldTransform.m[2][0] << " " << object.worldTransform.m[2][1] << " " << object.worldTransform.m[2][2] << " " << object.worldTransform.m[2][3]<< " " 
			<< object.worldTransform.m[3][0] << " " << object.worldTransform.m[3][1] << " " << object.worldTransform.m[3][2] << " " << object.worldTransform.m[3][3];
	return file;
}


