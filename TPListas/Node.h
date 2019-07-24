#pragma once
#include "Wagon.h"

#define NULL nullptr

class Node
{
public:
	Node(Wagon* v, Node* n = NULL);
	~Node();

private:
	Wagon* wagon;
	Node* next;

	friend class List;
};
typedef Node *pnode;
