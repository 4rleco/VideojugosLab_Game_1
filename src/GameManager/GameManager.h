#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

#include "Objects/Player.h"
#include "Objects/Obstacle.h"

using namespace sf;
using namespace std;

class GameManager
{
private:
	Player* player;

	Obstacle obstacle;

	Clock clock;

	Time dt;

	Font font;

	Text text;

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

	void Score(float& score);

	void ScoreText(int score);

	void ObstacleMovement();

	bool PlayerNObstacleCollision(bool& collision);

	void DrawGame();
};