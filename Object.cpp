#include "Object.h"

using namespace std;
using namespace DirectX;

Object::Object(string filename, XMFLOAT4X4 worldTransform)
{
	this->worldTransform = worldTransform;

	bool result = true;
	ifstream file(filename);

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
		throw runtime_error("Failed to load file: " + filename);
	}
	file.close();
}

Object::~Object()
{
}


