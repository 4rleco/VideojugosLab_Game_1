#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
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
	Obstacle obstacle1;

	Floor floor;

	Music* backgroundMusic;

	SoundBuffer menuOptionBuffer; 
	Sound menuOption;

	SoundBuffer changeSceneBuffer;
	Sound changeScene;

	SoundBuffer jumpBuffer;
	Sound jump;

	SoundBuffer deathBuffer;
	Sound death;

	Texture floorTexture;
	Sprite floorSprite;

	Event event;

	Clock clock;

	Time dt;

	Font font;

	Text score;

	Text menu;

	Text game;

	Text credits;

	Text exit;

	RenderWindow* window;

	int screenWidth;
	int screenHeight;

	bool grounded;

	bool isAlive;

public:
	GameManager();
	~GameManager();

	void DrawMenu(int& selection, float& timer, bool& actionPressed);

	void DrawGame();

	void DrawPause();

	void DrawDeath();

	void DrawCredits();

	void InitSounds();

	void InitTextures();

	void InitMusic();

	void InitGame();

	void RunGame();

	void CreateGame();

	void RestartClock();

	void StartRand();

	void PlayerMovement();

	void Score(float& score);

	void ScoreText(int scoreInt);

	void ObstacleMovement(Obstacle& obstacle);

	void FloorMovement();

	bool PlayerNObstacleCollision(Obstacle obstacle,
		bool& collision);

	bool PlayerNFloorCollision(bool& collision);

	bool PlayerFallsOfScreen(bool& collision);

	void GameLoop();
};