#include <iostream>
#include <DirectXMath.h>
#include <vector>

#include "BoundingBox.h"
#include "Triangle.h"
#include "Object.h"
#include "Quadtree.h"
#include "ObjectLoader.h"

using namespace std;
using namespace DirectX;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{
		ObjectLoader loader("assets/objectlist.txt");

		Quadtree tree(BoundingBox(XMFLOAT2(0, 0), XMFLOAT2(256, 256)));

		for (int i = 0; i < loader.GetSize(); i++)
		{
			tree.Insert(loader.GetAt(i));
		}
		tree.SaveToFile("assets/tree.txt");
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
	}
	cin.get();
	return 0;
}