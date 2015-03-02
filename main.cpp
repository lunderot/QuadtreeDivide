#include <iostream>
#include <DirectXMath.h>

#include "BoundingBox.h"
#include "Triangle.h"
#include "Object.h"

using namespace std;
using namespace DirectX;

int main()
{
	BoundingBox box(XMFLOAT2(0, 0), XMFLOAT2(10, 10));
	Triangle triangle(XMFLOAT3(1, 1, 0), XMFLOAT3(1, 3, 0), XMFLOAT3(4, 1, 0));

	cout << box.IsTriangleWithin(triangle) << endl;

	Object object("assets/triangle.obj");

	for (int i = 0; i < object.faces.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << object.faces[i].vertices[j].x << " "
				<< object.faces[i].vertices[j].y << " "
				<< object.faces[i].vertices[j].z << endl;
		}
	}
	

	cin.get();
	return 0;
}