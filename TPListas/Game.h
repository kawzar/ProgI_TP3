#pragma once
#include <SFML/Graphics.hpp>
#include "List.h"
#include "Locomotive.h"

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
	Wagon*wagons[3];
	RenderWindow *window;
	Texture txBackground;
	Sprite background;
	const float wagonDistance = 65.0f;
	float platforms[5];

	void InitWindow();
	void Update();
	void Draw();
};

