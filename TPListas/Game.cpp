#include "pch.h"
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
	wagons[1] = new Wagon(150.f, positions[1], number, positions, false);
	wagons[2] = new Wagon(150.f, positions[1], number, positions, false);
}


Game::~Game()
{
}

void Game::Update() 
{
	if (currentProblem == NULL)
	{
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

	for (int i = 0; i < 3; i++)
	{
		if (!wagons[i]->IsInList() && currentProblem == NULL) 
		{
			if (wagons[i]->Intersects(train.First()->GetBounds()))
			{
				currentWagon = wagons[i];
				currentProblem = new Problem();
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
		case Event::KeyPressed:
			if (currentProblem != NULL)
			{
				switch (evt.key.code)
				{
				case Keyboard::Num0:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 0 && currentWagon->Value() == 0);
					break;
				case Keyboard::Num1:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 1 && currentWagon->Value() == 1);
					break;
				case Keyboard::Num2:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 2 && currentWagon->Value() == 2);
					break;
				case Keyboard::Num3:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 3 && currentWagon->Value() == 3);
					break;
				case Keyboard::Num4:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 4 && currentWagon->Value() == 4);
					break;
				case Keyboard::Num5:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 5 && currentWagon->Value() == 5); 
					break;
				case Keyboard::Num6:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 6 && currentWagon->Value() == 6);
					break;
				case Keyboard::Num7:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 7 && currentWagon->Value() == 7);
					break;
				case Keyboard::Num8:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 8 && currentWagon->Value() == 8);
					break;
				case Keyboard::Num9:
					CheckWinLoseConditionForWagon(currentProblem->Value() == 9 && currentWagon->Value() == 9);
					break;
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
		currentWagon = NULL;
		delete currentProblem;
		currentProblem = NULL;
	}
	else
	{
		train.Delete(train.Last());
	}
}