#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Problem
{
public:
	Problem();
	~Problem();
	void Draw(RenderWindow* wnd);
	void Update();
	int Value();
private:
	Text text;
	Font font;
	Text problemText;
	int x, y, z, result;
};

