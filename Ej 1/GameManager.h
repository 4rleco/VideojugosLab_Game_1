#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

#include "Player.h"
#include "Obstacle.h"

using namespace sf;
using namespace std;

class GameManager
{
private:
	Player* player;

	Obstacle obstacle;

	Clock clock;

	Time dt;

	RenderWindow* window;

	int screenWidth;
	int screenHeight;

	bool grounded;

	bool isAlive;

public:
	GameManager(RenderWindow* window);
	~GameManager();

	void InitGame(RectangleShape& floor);

	void RunGame();

	void CreateGame();

	void RestartClock();

	void StartRand();

	void PlayerMovement();

	void ObstacleMovement();

	void DrawGame();
};