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

	srand(std::time(NULL));

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

	wagons[0] = new Wagon(150.f, positions[1], -1, positions, false);
	wagons[1] = new Wagon(150.f, positions[2], -1, positions, false);
	wagons[2] = new Wagon(150.f, positions[3], -1, positions, false);

	InitSound();
}


Game::~Game()
{
}

void Game::Update() 
{
	if (!isCurrentProblem)
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
					InitClock();
				}
			}
		}
	}

	if (isCurrentProblem)
	{
		UpdateClock();
	}
}

void Game::Draw() 
{
	window->clear();
	train.Draw(window);
	
	if (currentProblem != NULL)
	{
		currentProblem->Draw(window);
		window->draw(txtTime);
	}

	for (int i = 0; i < 3; i++) {
		if (wagons[i] != NULL && !wagons[i]->IsInList())
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
		currentWagon->SetValue(currentProblem->Value());
		train.Insert(currentWagon);
		currentWagon->MarkInList();
		correctSound.play();
		cout << "Win" << endl;
	}
	else
	{
		train.Delete(train.Last());
		delete currentWagon;
		currentWagon = NULL;
		failSound.play();
		cout << "Lose" << endl;
	}

	delete currentProblem;
	currentProblem = NULL;
	isCurrentProblem = false;
}

void Game::InitClock() {
	time = sf::seconds(30.0f);
	int seconds = time.asSeconds();

	if (!font.loadFromFile("Fonts/Less.otf"))
	{
		cout << "Couldn't load font";
	}

	txtTime = Text(std::to_string(seconds), font, 15);
	txtTime.setFillColor(sf::Color::White);
	txtTime.setPosition(15, 15);
}

void Game::UpdateClock() {
	int previousSecond = time.asSeconds();
	time -= clock.restart();

	int seconds = time.asSeconds();
	
	if (seconds <= 0)
	{
		CheckWinLoseConditionForWagon(false);
	}

	txtTime.setString(std::to_string(seconds));

	if (seconds != previousSecond) {
		clockSound.play();
	}
}

void Game::InitSound()
{
	correctSb.loadFromFile("Sounds/smw_coin.wav");
	failSb.loadFromFile("Sounds/explosion.wav");
	clockSb.loadFromFile("Sounds/tick.wav");

	correctSound.setBuffer(correctSb);
	failSound.setBuffer(failSb);
	clockSound.setBuffer(clockSb);
}