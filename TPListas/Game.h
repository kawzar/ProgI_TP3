#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "List.h"
#include "Locomotive.h"
#include "Wagon.h"
#include "Problem.h"
#include "Door.h"

using namespace sf;
using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Loop();

private:
	List train;
	Wagon* wagons[3];
	RenderWindow *window;
	Texture txBackground;
	Sprite background;
	const float wagonDistance = 65.0f;
	float platforms[5];
	int amountOfWagons = 2; 
	Text txtGameOver;
	Door* door;
	bool isGameOver, isWin;

	// Problems
	Problem* currentProblem;
	Wagon* currentWagon;
	string input;
	int inputResult;
	bool isCurrentProblem = false;

	// Clock
	Clock clock;
	Time time;
	Text txtTime;
	Font font;

	// Sound
	SoundBuffer correctSb;
	SoundBuffer failSb;
	SoundBuffer clockSb;
	Sound clockSound;
	Sound failSound;
	Sound correctSound;

	void InitWindow();
	void Update();
	void Draw();
	void CheckWinLoseConditionForWagon(bool isWin);
	void InitClock();
	void UpdateClock();
	void EventHandling();
	void InitSound();
	void EndGame();
};

