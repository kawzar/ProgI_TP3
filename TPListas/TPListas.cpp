// TPListas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Game.h"

int main()
{

	srand(std::time(NULL));

	Game* game = new Game();
	game->Loop();
}
