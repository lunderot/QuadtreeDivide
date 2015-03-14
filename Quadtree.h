#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <DirectXMath.h>

#include "Object.h"
#include "BoundingBox.h"

class Quadtree
{
private:
	class Node
	{
	public:
		Node();
		~Node();
		Node* child[4];
		std::vector<Object*> objects;
	};
	Node* root;
	BoundingBox rootBoundingBox;
	const int MAX_DEPTH = 4;
public:
	Quadtree(BoundingBox rootBoundingBox);
	Quadtree(std::string filename);
	~Quadtree();
	void SaveToFile(std::string filename);
	void Insert(Object* object);

private:
	void Clean(Node* currentNode);
	void Insert(Object* object, Node* currentNode, BoundingBox box, int depth);
	void WriteNode(std::ofstream& file, Node* currentNode);
	Node* ReadNode(std::ifstream& file);
};

