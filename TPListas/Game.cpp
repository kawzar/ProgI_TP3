#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	srand(time(NULL));

	int number = rand() % 10 + 1;

	Locomotive* l = new Locomotive(50, 150.f, -1);
	Wagon* w = new Wagon(150.f, 150.f, number);
	number = rand() % 10 + 1;
	Wagon* w2 = new Wagon(150.f, 150.f, number);
	
	number = rand() % 10 + 1;
	Wagon* w3 = new Wagon(150.f, 150.f, number);


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
	window = new RenderWindow(VideoMode(800, 600), "TP Listas");
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