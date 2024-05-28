#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->clock = Clock();
	this->dt = Time();
	this->font = Font();

	this->score = Text();
	this->menu = Text();

	this->window = window;

	this->screenWidth = 1080;
	this->screenHeight = 720;

	this->player = new Player(screenWidth / 4, screenWidth / 4, 650.0f, 650.0f, 50.0f, 100.0f);

	this->obstacle = Obstacle::Obstacle();

	this->floor = Floor::Floor();

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

	obstacle.CreateObstacle();

	floor.CreateFloor();
}

void GameManager::RestartClock()
{
	this->dt = this->clock.restart();
}

void GameManager::StartRand()
{
	srand(time(NULL));
}

void GameManager::PlayerMovement()
{
	float playerPosX = player->GetPosX();
	float playerPosY = player->GetPosY();

	float gravity = 100.0f;

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

		PlayerNFloorCollision(grounded);		
	}
}

void GameManager::Score(float& score)
{
	score += dt.asSeconds();
}

void GameManager::ScoreText(int scoreInt)
{
	string score_txt = "Score " + to_string(scoreInt);

	score = Text(score_txt, font);
	score.setCharacterSize(20);
	score.setStyle(Text::Bold);
	score.setFillColor(Color::Yellow);
	score.setPosition(800.0f, 2.0f);
}

void GameManager::ObstacleMovement()
{
	float speed = 300.0f;

	speed *= dt.asSeconds();

	obstacle.SetPosX(speed);

	obstacle.UpdateObstaclePosition();

	obstacle.RestarPosiion();
}

void GameManager::FloorMovement()
{
	float speed = 200.0f;

	speed *= dt.asSeconds();

	floor.SetPosX(speed);

	floor.UpdateFloorPosition();

	floor.RestarPosition();
}

bool GameManager::PlayerNObstacleCollision(bool& collision)
{
	if ((player->GetPosX() + player->GetWidh() >= obstacle.GetPosX()) &&
		(player->GetPosY() + player->GetHeight() >= obstacle.GetPosY()) &&
		(player->GetPosX() <= obstacle.GetPosX() + obstacle.GetWidh()) &&
		(player->GetPosY() <= obstacle.GetPosY() + obstacle.GetHeight()))
	{
		return collision = true;
	}
}

bool GameManager::PlayerNFloorCollision(bool& collision)
{
	if ((player->GetPosX() + player->GetWidh() >= floor.GetPosX()) &&
		(player->GetPosY() + player->GetHeight() >= floor.GetPosY()) &&
		(player->GetPosX() <= floor.GetPosX() + floor.GetWidh()) &&
		(player->GetPosY() <= floor.GetPosY() + floor.GetHeight()))
	{
		return collision = true;
	}
}

bool GameManager::PlayerFallsOfScreen(bool& collision)
{
	if (player->GetPosY() + player->GetHeight()/2 > screenHeight)
	{
		return collision = true;
	}

	if (player->GetPosY() <= 0)
	{
		player->SetPosY(0);
	}
}

void GameManager::DrawGame()
{
	window->draw(floor.GetFloorShape());

	window->draw(player->GetPlayerShape());

	window->draw(obstacle.GetObstacleShape());

	window->draw(score);
}

void GameManager::InitGame()
{
	window = new RenderWindow(VideoMode(screenWidth, screenHeight), "SideScroller");

	font.loadFromFile("font/arial.ttf");

	StartRand();

	CreateGame();
}

void GameManager::DrawMenu()
{
	enum mainmenu
	{
		game,
		credits
	};

	int selection = 0;

	selection = mainmenu::game;

	switch (selection)
	{
	case game:
		break;
	case credits:
		break;
	}	

	menu = Text("Menu", font);
	menu.setCharacterSize(100);
	menu.setStyle(Text::Bold);
	menu.setFillColor(Color::White);
	menu.setPosition(420, 200);

	window->draw(menu);
}

void GameManager::GameLoop()
{
	float score = 0;

	bool collision = false;

	while (window->isOpen() && player->IsAlive(collision) == false)
	{
		RestartClock();

		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		PlayerMovement();

		ObstacleMovement();

		FloorMovement();

		Score(score);

		ScoreText(score);

		PlayerNObstacleCollision(collision);

		PlayerFallsOfScreen(collision);

		window->clear();
		DrawGame();
		window->display();
	}
}

void GameManager::RunGame()
{
	InitGame();

	while (window->isOpen() /*&& player->IsAlive(collision) == false*/)
	{
		RestartClock();

		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}


		
		window->clear();
		DrawMenu();
		window->display();
	}	
}