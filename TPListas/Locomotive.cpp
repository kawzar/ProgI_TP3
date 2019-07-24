#include "Locomotive.h"



Locomotive::Locomotive(float xpos, float ypos, int v) : Wagon(xpos, ypos, v)
{
	if (!texture.loadFromFile("Images/locomotora.png")) { }
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y);

	text.setString("");
}


Locomotive::~Locomotive()
{
}

void Locomotive::Draw(RenderWindow* wnd)
{
	wnd->draw(sprite);
	wnd->draw(text);
}