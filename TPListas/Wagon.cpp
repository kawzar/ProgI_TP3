#include "Wagon.h"
#include <iostream>

using namespace std;

Wagon::Wagon(float xpos, float ypos, int v, float* pos)
{
	x = xpos;
	y = ypos;
	value = v;
	currentPosition = 0;

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

	cout << "Value " << value << endl;
	text = Text(std::to_string(value), font, 30);
	text.setFillColor(sf::Color::Yellow);
	text.setOrigin(text.getOrigin().x, sprite.getOrigin().y - 10);
	text.setPosition(x, y);
}


Wagon::~Wagon()
{
}

void Wagon::Draw(RenderWindow* wnd)
{
	wnd->draw(sprite);
	wnd->draw(text);
}

void Wagon::Update() 
{
	x += velocity;

	if (x >= 1280.f && currentPosition < 4) 
	{
		currentPosition++;
		y = positions[currentPosition];
		x = 0.f;
	}
	sprite.setPosition(x + velocity, y);
	text.setPosition(x, y);
}

void Wagon::SetPosition(Vector2f v) 
{
	x = v.x;
	y = v.y;

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