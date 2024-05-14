#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->clock = Clock();
	this->dt = Time();
	this->window = window;

	this->screenWidth = 1080;
	this->screenHeight = 720;

	this->player = new Player(screenWidth / 4, screenWidth / 4, 650.0f, 650.0f, 100.0f, 50.0f);

	this->grounded = true;

	this->isAlive = true;
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

	float gravity = 90.0f;

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		playerPosY -= player->GetSpeed().y * dt.asSeconds() * 5;
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

void GameManager::InitGame(RectangleShape& floor)
{
	window = new RenderWindow(VideoMode(screenWidth, screenHeight), "SideScroller");

	float fwidth = screenWidth;
	float fheight = screenHeight;
	float FposX = 0.0f;
	float FposY = 680.0f;

	floor.setSize(Vector2f(fwidth, fheight));
	floor.setOutlineColor(Color::Red);
	floor.setOutlineThickness(5);
	floor.setPosition(FposX, FposY);

	CreateGame();
}

void GameManager::RunGame()
{
	RectangleShape floor;

	InitGame(floor);

	while (window->isOpen())
	{
		RestartClock();

		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		PlayerMovement();

		window->clear();
		window->draw(floor);
		DrawGame();
		window->display();
	}
}