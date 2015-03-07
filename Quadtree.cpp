#include "Quadtree.h"

using namespace std;

Quadtree::Node::Node()
{
	for (int i = 0; i < 4; i++)
	{
		child[i] = nullptr;
	}
}

Quadtree::Quadtree(BoundingBox rootBoundingBox)
{
	this->root = new Node();
	this->rootBoundingBox = rootBoundingBox;
}


Quadtree::~Quadtree()
{
	Clean(root);
}

void Quadtree::Clean(Node* currentNode)
{
	if (currentNode)
	{
		for (int i = 0; i < 4; i++)
		{
			Clean(currentNode->child[i]);
		}
	}
	delete currentNode;
}

void Quadtree::SaveToFile(std::string filename)
{
}

void Quadtree::Insert(Object* object, Node* currentNode, BoundingBox box, int depth)
{
	if (depth < MAX_DEPTH && box.IsObjectWithin(*object)) //Check if we haven't reched max depth and object is within the bounding box
	{
		//Loop through the child bounding boxes
		bool result = false;
		for (int i = 0; i < 4 && !result; i++)
		{
			BoundingBox childBox = box.GetChildBoundingBox(i);
			if (childBox.IsObjectWithin(*object)) //Found the child bounding box the object fits into
			{
				currentNode->child[i] = new Node();
				Insert(object, currentNode->child[i], childBox, depth + 1);
				result = true;
			}
		}
		if (!result) //Reached the smallest bounding box the object can fit into
		{
			currentNode->objects.push_back(object);
		}
	}
	else if (depth == MAX_DEPTH && box.IsObjectWithin(*object))
	{
		currentNode->objects.push_back(object);
	}
}

void Quadtree::Insert(Object* object)
{
	Insert(object, root, rootBoundingBox, 0);
}
