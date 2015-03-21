#include "Quadtree.h"

using namespace std;
using namespace DirectX;

Quadtree::Node::Node()
{
	for (int i = 0; i < 4; i++)
	{
		child[i] = nullptr;
	}
}

Quadtree::Node::~Node()
{
}

Quadtree::Quadtree(BoundingBox rootBoundingBox)
{
	this->root = new Node();
	this->rootBoundingBox = rootBoundingBox;
}

Quadtree::Quadtree(std::string filename)
{
	ifstream file(filename);
	if (file.good())
	{
		XMFLOAT2 position;
		XMFLOAT2 size;
		file >> position.x >> position.y >> size.x >> size.y;
		rootBoundingBox = BoundingBox(position, size);
		root = ReadNode(file);
	}
	file.close();
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
		delete currentNode;
		currentNode = nullptr;
	}
}

void Quadtree::SaveToFile(std::string filename)
{
	ofstream file(filename);
	if (file.good())
	{
		file	<< rootBoundingBox.GetPosition().x << " " << rootBoundingBox.GetPosition().y << " "
				<< rootBoundingBox.GetSize().x << " " << rootBoundingBox.GetSize().y << endl;
		WriteNode(file, root);
	}
	file.close();
}

void Quadtree::WriteNode(std::ofstream& file, Node* currentNode)
{
	for (vector<Object*>::iterator i = currentNode->objects.begin(); i != currentNode->objects.end(); ++i)
	{
		file << **i << endl;
	}
	for (int i = 0; i < 4; i++)
	{
		if (currentNode->child[i])
		{
			file << "c " << i << endl;
			WriteNode(file, currentNode->child[i]);
		}
	}
	file << "e"<< endl;
}
Quadtree::Node* Quadtree::ReadNode(std::ifstream& file)
{
	string command;
	
	Node* currentNode = new Node();
	while (!file.eof())
	{
		file >> command;
		if (command == "o")
		{
			string objectFilename;
			XMFLOAT4X4 worldTransform;
			file >> objectFilename;
			file >> worldTransform.m[0][0] >> worldTransform.m[0][1] >> worldTransform.m[0][2] >> worldTransform.m[0][3]
				>> worldTransform.m[1][0] >> worldTransform.m[1][1] >> worldTransform.m[1][2] >> worldTransform.m[1][3]
				>> worldTransform.m[2][0] >> worldTransform.m[2][1] >> worldTransform.m[2][2] >> worldTransform.m[2][3]
				>> worldTransform.m[3][0] >> worldTransform.m[3][1] >> worldTransform.m[3][2] >> worldTransform.m[3][3];

			currentNode->objects.push_back(new Object(objectFilename, worldTransform));
		}
		else if (command == "c")
		{
			int childNum;
			file >> childNum;
			currentNode->child[childNum] = ReadNode(file);
		}
		else if (command == "e")
		{
			return currentNode;
		}
	}
}


void Quadtree::Insert(Object* object, Node* currentNode, BoundingBox box, int depth)
{
	if (depth < MAX_DEPTH && box.IsObjectWithin(*object)) //Check if we haven't reached max depth and object is within the bounding box
	{
		//Loop through the child bounding boxes
		bool result = false;
		for (int i = 0; i < 4 && !result; i++)
		{
			BoundingBox childBox = box.GetChildBoundingBox(i);
			if (childBox.IsObjectWithin(*object)) //Found the child bounding box the object fits into
			{
				if (!currentNode->child[i])
				{
					currentNode->child[i] = new Node();
				}
				
				Insert(object, currentNode->child[i], childBox, depth + 1);
				result = true;
			}
		}
		if (!result) //Reached the smallest bounding box the object can fit into
		{
			cout << "DEBUG: Added object in BoundingBox((" << box.GetPosition().x << " " << box.GetPosition().y << "), (" << box.GetSize().x << " " << box.GetSize().y << "))" <<
					" at depth " << depth << endl;
			currentNode->objects.push_back(object);
		}
	}
	else if (depth == MAX_DEPTH && box.IsObjectWithin(*object))
	{
		cout << "DEBUG: Added object in BoundingBox((" << box.GetPosition().x << " " << box.GetPosition().y << "), (" << box.GetSize().x << " " << box.GetSize().y << "))" <<
			" at max depth " << depth << endl;
		currentNode->objects.push_back(object);
	}
}

void Quadtree::Insert(Object* object)
{
	Insert(object, root, rootBoundingBox, 0);
}
