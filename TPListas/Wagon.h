#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wagon
{
public:
	Wagon(float x, float y, int value, float* positions, bool inList);
	~Wagon();
	void Draw(RenderWindow* wnd);
	void Update();
	bool IsInList();

	void SetPosition(Vector2f v);
	Vector2f GetPosition();
	float GetWidth();
	int Value();
	void MarkInList();

	bool Intersects(sf::FloatRect rect);

	sf::FloatRect GetBounds();


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
	bool isInList = false;
friend class Node;
friend class List;
};

