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
	try
	{
		ObjectLoader loader("assets/objectlist.txt");


		//Load objects and thier world transform
		//Make a boundingbox and test if the object is inside
		//Add it to the quadtree
		//Save to file


		
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
	}
	

	cin.get();
	return 0;
}