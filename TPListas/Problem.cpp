#include "Problem.h"
#include <sstream>



Problem::Problem()
{
	font.loadFromFile("Fonts/Less.otf");

	text = Text("Ingrese el resultado de la operacion: ", font, 15);
	text.setFillColor(sf::Color::Magenta);
	text.setPosition(400, 250);

	x = rand() % 10;
	y = rand() % 10;
	z = rand() % 10;
	std::stringstream ss;
	ss << x << " + " << y << " + " << z << " = ___";
	problemText = Text("", font, 15);
	problemText.setString(ss.str());
	problemText.setPosition(450, 270);
	result = x + y + z;
}


Problem::~Problem()
{
}

void Problem::Update() 
{

}

void Problem::Draw(RenderWindow * wnd)
{
	wnd->draw(text);
	wnd->draw(problemText);
}

int Problem::Value()
{
	return result;
}