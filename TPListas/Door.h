#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Door
{
public:
	Door(float x, float y);
	~Door();

	void draw(RenderWindow * window);
	FloatRect getBounds();

private:
	Texture _tx;
	Sprite _sprite;
};

