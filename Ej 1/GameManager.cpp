#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->clock = Clock();
	this->dt = Time();
	this->window = window;

	this->screenWidth = 1080;
	this->screenHeight = 720;

	this->player = new Player(0.0f, 0.0f, 650.0f, 650.0f, 100.0f, 50.0f);

	this->grounded = true;
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

	float gravity = 40.0f;

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		playerPosX += player->GetSpeed().x * dt.asSeconds();
		player->SetPosX(playerPosX);
		player->UpdatePosition(playerPosX, playerPosY);
	}


	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		playerPosY -= player->GetSpeed().y * dt.asSeconds();
		player->SetPosY(playerPosY);
		player->UpdatePosition(playerPosX, playerPosY);
		grounded = false;
	}


	if (grounded == false)
	{
		playerPosY += gravity * dt.asSeconds();
		player->SetPosY(playerPosY);
		player->UpdatePosition(playerPosX, playerPosY);

		if (playerPosY >= 650.0f)
		{
			grounded = true;
		}
	}
}

void GameManager::DrawGame()
{
	window->draw(player->GetPlayerShape());
}