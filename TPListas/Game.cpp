﻿#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	float positions[] = { 142, 256, 370, 485, 610};
	currentProblem = NULL;
	currentWagon = NULL;

	for (int i = 0; i < 5; i++)
	{
		platforms[i] = positions[i];
	}

	srand(time(NULL));

	int number = rand() % 10 + 1;

	Locomotive* l = new Locomotive(30.f, positions[0], -1, positions);
	Wagon* w = new Wagon(150.f, positions[0], number, positions, true);
	number = rand() % 10 + 1;
	Wagon* w2 = new Wagon(150.f, positions[0], number, positions, true);
	
	number = rand() % 10 + 1;
	Wagon* w3 = new Wagon(150.f, positions[0], number, positions, true);


	InitWindow();
	train.Insert(l);
	train.Insert(w);
	train.Insert(w2);
	train.Insert(w3);

	wagons[0] = new Wagon(150.f, positions[1], number, positions, false);
	wagons[1] = new Wagon(150.f, positions[2], number, positions, false);
	wagons[2] = new Wagon(150.f, positions[3], number, positions, false);
}


Game::~Game()
{
}

void Game::Update() 
{
	if (!isCurrentProblem)
	{
		cout << "Current problem null" << endl;
		train.Update();

		for (int i = 0; i < 3; i++)
		{
			if (!wagons[i]->IsInList())
			{
				wagons[i]->Update();
			}
		}
	}
	else
	{
		currentProblem->Update();
	}

	for (int i = 0; i < 3 && !isCurrentProblem; i++)
	{
		if (!wagons[i]->IsInList()) 
		{
			if (wagons[i]->Intersects(train.First()->GetBounds()))
			{
				if (currentWagon != wagons[i])
				{
					cout << "Collided" << endl;
					currentWagon = wagons[i];
					currentProblem = new Problem();
					isCurrentProblem = true;
				}
			}
		}
	}
}

void Game::Draw() 
{
	window->clear();
	train.Draw(window);
	
	if (currentProblem != NULL)
	{
		currentProblem->Draw(window);
	}

	for (int i = 0; i < 3; i++) {
		if (!wagons[i]->IsInList())
		{
			wagons[i]->Draw(window);
		}
	}

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
		EventHandling();
		Draw();
	}
}

void Game::EventHandling()
{
	Event evt;
	while (window->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			window->close();
			break;
		case Event::TextEntered:
			if (isCurrentProblem)
			{
				if (evt.text.unicode > 47 && evt.text.unicode < 58)//si lo que se escribi� se encuentra entre 0 y 9
				{
					input += evt.text.unicode;//voy agregando n�meros a la cadena
					cout << input << endl;//muestro lo que voy agregando
				}
				if (evt.text.unicode == 13)//si presiono ENTER aviso que no quiero leer m�s n�meros
				{
					inputResult = stoi(input);
					input = "";
					cout << input << endl;
					CheckWinLoseConditionForWagon(inputResult == currentProblem->Value());
				}
			}
		}
	}
}

void Game::CheckWinLoseConditionForWagon(bool isWin)
{
	if (isWin)
	{
		train.Insert(currentWagon);
		currentWagon->MarkInList();
		cout << "Win" << endl;
	}
	else
	{
		train.Delete(train.Last());
		delete currentWagon;
		cout << "Lose" << endl;
	}

	delete currentProblem;
	currentProblem = NULL;
	isCurrentProblem = false;
}