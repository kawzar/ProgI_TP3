#include "pch.h"
#include "Door.h"


Door::Door(float x, float y)
{
	_tx.loadFromFile("Images/puerta.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);
	_sprite.setPosition(x, y);
}


Door::~Door()
{
}

void Door::draw(RenderWindow * window)
{
	window->draw(_sprite);
}

FloatRect Door::getBounds()
{
	return _sprite.getGlobalBounds();
}
