#include "pch.h"
#include "Node.h"


Node::Node(Wagon* v, Node* n)
{
	wagon = v;
	next = n;
}


Node::~Node()
{
	delete wagon;
}
