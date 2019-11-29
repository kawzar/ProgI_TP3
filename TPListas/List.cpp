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

Wagon* List::First() {
	current = first;
	return first->wagon;
}

Wagon* List::Last() {
	current = first;
	if (!IsEmpty()) {
		while (current->next) {
			Next();
		}
	}

	return current->wagon;
}

bool List::IsEmpty() {
	return first == NULL;
}

void List::Insert(Wagon* v) {
	pnode previous;

	if (IsEmpty() || first->wagon->value >= v->value) {
		first = new Node(v, NULL);
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
	cout << "Delete" << endl;

	do {
		previous = node;
		node = node->next;
	} while (node != NULL && node->wagon->value < v->value);


	if (!node || node->wagon->value != v->value) {
		cout << "return" << endl;
		return;
	}
	else 
	{ // delete node
		if (!previous) { // first element
			first = node->next;
			cout << "first" << endl;
		}
		else { // other
			previous->next = node->next;
			cout << "other" << endl;
		}

		delete node;
		node = NULL;
	}

	OrderSprites();
}

void List::Update()
{
	OrderSprites(); 

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
	while (node != NULL && node->wagon != NULL && node->wagon->isInList) {
		node->wagon->Draw(wnd);
		node = node->next;
	}
}

void List::OrderSprites()
{
	pnode node = first;
	Wagon* lastWagon = first->wagon;
	bool isFirst = true;
	while (node != NULL) 
	{
		if (!isFirst) 
		{
			Vector2f newPosition = Vector2f(lastWagon->GetPosition().x - node->wagon->GetWidth(), lastWagon->GetPosition().y);
			node->wagon->SetPosition(newPosition);
			lastWagon = node->wagon;
		}
		else 
		{
			isFirst = false;
		}

		node = node->next;
	}
}