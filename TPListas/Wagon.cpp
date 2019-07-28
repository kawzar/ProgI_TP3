#include "Wagon.h"
#include <iostream>

using namespace std;

Wagon::Wagon(float xpos, float ypos, int v, float* pos, bool inList)
{
	x = xpos;
	y = ypos;
	value = v;
	currentPosition = 0;
	isInList = inList;

	for (int i = 0; i < 5; i++)
	{
		positions[i] = pos[i];
	}

	if (!texture.loadFromFile("Images/vagon.png")) 
	{ 
		cout << "Error loading sprite"; 
	}
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y);

	if (!font.loadFromFile("Fonts/Less.otf"))
	{
		cout << "Couldn't load font";
	}

	SetValue(value);
}


Wagon::~Wagon()
{
}

void Wagon::Draw(RenderWindow* wnd)
{
	wnd->draw(sprite);

	if (value > 0)
	{
		wnd->draw(text);
	}
}

void Wagon::Update() 
{
	if (isInList)
	{
		x += velocity;
	}

	SetPosition(Vector2f(x, y));
}

void Wagon::SetPosition(Vector2f v) 
{
	x = v.x;
	y = v.y;

	// Reposition if out of the screen
	if (x >= 1400 && currentPosition <= 4)
	{
		currentPosition++;
		y = positions[currentPosition];
		x = 0.f;
	}

	sprite.setPosition(x, y);
	text.setPosition(x, y);
}

sf::Vector2f Wagon::GetPosition() 
{
	return Vector2f(x, y);
}

float Wagon::GetWidth()
{
	return sprite.getGlobalBounds().width;
}

bool Wagon::Intersects(sf::FloatRect rect) 
{
	return sprite.getGlobalBounds().intersects(rect);
}

sf::FloatRect Wagon::GetBounds(){
	return sprite.getGlobalBounds();
}

bool Wagon::IsInList() {
	return isInList;
}

int Wagon::Value()
{
	return value;
}

void Wagon::MarkInList()
{
	isInList = true;
}

void Wagon::SetValue(int v)
{
	value = v;
	text = Text(std::to_string(value), font, 30);
	text.setFillColor(sf::Color::Yellow);
	text.setOrigin(text.getOrigin().x, sprite.getOrigin().y - 10);
	text.setPosition(x, y);
}