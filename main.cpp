#include <iostream>
#include <DirectXMath.h>

#include "BoundingBox.h"
#include "Triangle.h"

using namespace std;
using namespace DirectX;

int main()
{
	BoundingBox box(XMFLOAT2(0, 0), XMFLOAT2(10, 10));
	Triangle triangle(XMFLOAT3(1, 1, 0), XMFLOAT3(1, 3, 0), XMFLOAT3(4, 1, 0));

	cout << box.IsTriangleWithin(triangle) << endl;
	cin.get();

	return 0;
}