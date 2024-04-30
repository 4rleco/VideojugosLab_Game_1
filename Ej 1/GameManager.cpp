#include "GameManager.h"

GameManager::GameManager()
{	
	this->screenWidth = 1080;
	this->screenHeight = 720;
}

GameManager::~GameManager()
{

}

void GameManager::PlayerMovement()
{
	float playerPosX = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		playerPosX += player.GetSpeed().x * dt.asSeconds();
		player.SetPosX(playerPosX);
		player.ChangePosition(player.GetPosX(), player.GetPosY());
	}
}