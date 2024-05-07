#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->clock = Clock();
	this->dt = Time();
	this->window = window;

	this->screenWidth = 1080;
	this->screenHeight = 720;
	this->player = new Player(0.0f, 0.0f, 650.0f, 650.0f, 100.0f, 50.0f);
}

GameManager::~GameManager()
{
	delete player;
}

void GameManager::CreateGame()
{
	this->player->CreatePlayer();
}

void GameManager::RestartClock()
{
	this->dt = this->clock.restart();
}

void GameManager::PlayerMovement()
{
	float playerPosX = player->GetPosX();
	float playerPosY = player->GetPosY();

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		cout << playerPosX << endl;
 
		playerPosX += player->GetSpeed().x * dt.asSeconds();

		cout << playerPosX << endl;

		player->SetPosX(playerPosX);		
		player->UpdatePosition(playerPosX, playerPosY);
	}
}

void GameManager::DrawGame()
{
	window->draw(player->GetPlayerShape());
}