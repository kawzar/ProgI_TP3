#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	float positions[] = { 142, 256, 370, 485, 610};
	currentProblem = NULL;
	currentWagon = NULL;
	amountOfWagons = 3; // include locomotive
	isGameOver = false;
	
	int number = rand() % 10 + 1;


	// Insert initial wagons
	Locomotive* l = new Locomotive(30.f, positions[0], -1, positions);
	Wagon* w = new Wagon(150.f, positions[0], number, positions, true);	
	number = rand() % 10 + 1;
	Wagon* w2 = new Wagon(150.f, positions[0], number, platforms, true);
	   	
	train.Insert(l);
	train.Insert(w);
	train.Insert(w2);


	// Create individual wagons
	wagons[0] = new Wagon(rand() % 900 + 200, positions[1], -1, positions, false);
	wagons[1] = new Wagon(rand () % 900 + 200, positions[2], -1, positions, false);	
	wagons[2] = new Wagon(rand () % 900 + 200, positions[3], -1, positions, false);
	   

	// Create door
	door = new Door(1100.f, positions[4]);

	InitWindow();
	InitSound();
}


Game::~Game()
{
}

void Game::Update() 
{
	 // check collision with dooor
	if (door->getBounds().intersects(train.First()->GetBounds()))
	{
		isGameOver = true;
		isWin = true;
	}

	// wether to update train or problem in screen
	if (!isCurrentProblem)
	{
		train.Update();

		for (int i = 0; i < 3; i++)
		{
			if (wagons[i] != NULL && !wagons[i]->IsInList())
			{
				wagons[i]->Update();
			}
		}
	}
	else
	{
		currentProblem->Update();
	}


	// Check collision with individual wagons
	for (int i = 0; i < 3 && !isCurrentProblem; i++)
	{
		if (wagons[i] != NULL && !wagons[i]->IsInList()) 
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


	// update clock if problem's on screen
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

	door->draw(window);

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
		if (!isGameOver) {
			Update();
			EventHandling();
			Draw();
		} 
		else {
			EndGame();
		}
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
				if (evt.text.unicode > 47 && evt.text.unicode < 58)
				{
					input += evt.text.unicode;
					cout << input << endl;
				}
				if (evt.text.unicode == 13)
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

void Game::CheckWinLoseConditionForWagon(bool win)
{
	if (win)
	{
		// Insert wagon in train
		currentWagon->SetValue(currentProblem->Value());
		train.Insert(currentWagon);
		currentWagon->MarkInList();
		correctSound.play();
		amountOfWagons++;
		currentWagon = NULL;
	}
	else
	{
		// Delete one wagon from train and also the current wagon
		train.Delete(train.Last());
		delete currentWagon;
		currentWagon = NULL;
		failSound.play();
		amountOfWagons--;

		// Check global win condition
		if (amountOfWagons < 1)
		{
			isWin = false;
			isGameOver = true;
		}
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

void Game::EndGame()
{
	if (isWin) 
	{
		txtGameOver = Text("You won!", font, 15);
		txtGameOver.setFillColor(sf::Color::Green);

	}
	else 
	{
		txtGameOver = Text("You Lost!", font, 15);
		txtGameOver.setFillColor(sf::Color::Red);
	}

	txtTime.setFillColor(Color::Black);
	txtGameOver.setPosition(200, 250);

	window->clear(Color::Black);
	window->draw(txtGameOver);
	window->draw(txtTime);
	window->display();

	Event evt;
	while (window->pollEvent(evt))
	{
		if (evt.type == Event::Closed) {
			window->close();
		}
	}
}