#pragma once
#include "Wagon.h"
class Locomotive : public Wagon
{
public:
	Locomotive(float xpos, float ypos, int v, float* positions);
	~Locomotive();
	void Draw(RenderWindow * wnd);
};

