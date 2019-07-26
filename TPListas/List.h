#pragma once
#include "Node.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class List
{
public:
	List();
	~List();

	void Next();
	Wagon* First();
	Wagon* Last();
	bool IsEmpty();
	void Insert(Wagon* v);
	void Delete(Wagon* v);
	void Update();
	void Draw(RenderWindow* wnd);
private:
	pnode first;
	pnode current;

	void OrderSprites();
};