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
#include "Objects/Floor.h"

using namespace sf;
using namespace std;

class GameManager
{
private:
	Player* player;

	Obstacle obstacle;

	Floor floor;

	Clock clock;

	Time dt;

	Font font;

	Text score;

	Text menu;

	RenderWindow* window;

	int screenWidth;
	int screenHeight;

	bool grounded;

	bool isAlive;

public:
	GameManager(RenderWindow* window);
	~GameManager();

	void DrawMenu();

	void InitGame();

	void RunGame();

	void CreateGame();

	void RestartClock();

	void StartRand();

	void PlayerMovement();

	void Score(float& score);

	void ScoreText(int scoreInt);

	void ObstacleMovement();

	void FloorMovement();

	bool PlayerNObstacleCollision(bool& collision);

	bool PlayerNFloorCollision(bool& collision);

	bool PlayerFallsOfScreen(bool& collision);

	void GameLoop();

	void DrawGame();
};