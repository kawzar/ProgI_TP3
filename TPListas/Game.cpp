#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	float positions[] = { 142, 256, 370, 485, 610};

	for (int i = 0; i < 5; i++)
	{
		platforms[i] = positions[i];
	}

	srand(time(NULL));

	int number = rand() % 10 + 1;

	Locomotive* l = new Locomotive(30.f, positions[0], -1, positions);
	Wagon* w = new Wagon(150.f, positions[0], number, positions);
	number = rand() % 10 + 1;
	Wagon* w2 = new Wagon(150.f, positions[0], number, positions);
	
	number = rand() % 10 + 1;
	Wagon* w3 = new Wagon(150.f, positions[0], number, positions);


	InitWindow();
	train.Insert(l);
	train.Insert(w);
	train.Insert(w2);
	train.Insert(w3);

}


Game::~Game()
{
}

void Game::Update() 
{
	train.Update();
}

void Game::Draw() 
{
	window->clear();
	train.Draw(window);
	window->display();
}

void Game::InitWindow()
{
	window = new RenderWindow(VideoMode(1280, 720), "TP Listas");
	window->setMouseCursorVisible(true);
	window->setFramerateLimit(60);
}

void Game::Loop() 
{
	while (window->isOpen()) 
	{
		Update();
		Draw();
	}
}