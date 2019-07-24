#include "List.h"
#include "pch.h"
#include <iostream>

using namespace std;

List::List()
{
	first = current = NULL;
}


List::~List()
{
}

void List::Next() {
	if (current) {
		current = current->next;
	}
}

void List::First() {
	current = first;
}

void List::Last() {
	current = first;
	if (!IsEmpty()) {
		while (current->next) {
			Next();
		}
	}

}

bool List::IsEmpty() {
	return first == NULL;
}

void List::Insert(Wagon* v) {
	pnode previous;

	if (IsEmpty() || first->wagon->value > v->value) {
		first = new Node(v, first);
	}
	else 
	{
		previous = first;

		while (previous->next && previous->next->wagon->value <= v->value) {
			previous = previous->next;
		}

		previous->next = new Node(v, previous->next);
	}

	OrderSprites();
}

void List::Delete(Wagon* v) {
	pnode previous, node;

	node = first;
	previous = NULL;

	while (node && node->wagon->value < v->value) {
		previous = node;
		node = node->next;
	}

	if (!node || node->wagon->value != v->value) {
		return;
	}
	else 
	{ // delete node
		if (!previous) { // first element
			first = node->next;
		}
		else { // other
			previous->next = node->next;
		}
	}

	OrderSprites();
}

void List::Update()
{
	pnode node;
	node = first;
	while (node != NULL) {
		node->wagon->Update();
		node = node->next;
	}
}

void List::Draw(sf::RenderWindow * wnd)
{
	pnode node;
	node = first;
	while (node != NULL) {
		node->wagon->Draw(wnd);
		node = node->next;
	}
}

void List::OrderSprites()
{
	pnode node = first;
	sf::Vector2f lastPosition = first->wagon->GetPosition();
	bool isFirst = true;
	while (node) 
	{
		if (!isFirst) 
		{
			Vector2f newPosition = Vector2f(lastPosition.x - node->wagon->GetWidth(), node->wagon->GetPosition().y);
			node->wagon->SetPosition(newPosition);
			lastPosition = newPosition;

			cout << lastPosition.x << endl;
		}
		else 
		{
			isFirst = false;
		}

		node = node->next;
	}
}