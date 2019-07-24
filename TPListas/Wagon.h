#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wagon
{
public:
	Wagon(float x, float y, int value, float* positions);
	~Wagon();
	void Draw(RenderWindow* wnd);
	void Update();

	void SetPosition(Vector2f v);
	Vector2f GetPosition();
	float GetWidth();

protected:
	int value;
	Sprite sprite;
	Texture texture;
	Text text;
	Font font;
	float x, y;
	float velocity = 3.f;
	float positions[5];
	int currentPosition;

friend class Node;
friend class List;
};

