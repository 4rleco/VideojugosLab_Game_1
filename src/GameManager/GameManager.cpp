#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->clock = Clock();
	this->dt = Time();
	this->font = Font();

	this->score = Text();
	this->menu = Text();
	this->game = Text();
	this->credits = Text();
	this->exit = Text();

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
	if (player->GetPosY() + player->GetHeight() / 2 > screenHeight)
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

void GameManager::DrawMenu(int& selection, float& timer, bool& actionPressed)
{
	enum MainMenu
	{
		Game,
		Credits,
		Exit
	};

	int coolDown = 3;

	int firstOption = Game;
	int lastOption = Exit;

	menu = Text("Menu", font);
	menu.setCharacterSize(100);
	menu.setStyle(Text::Bold);
	menu.setFillColor(Color::White);
	menu.setPosition(400, 200);

	game = Text("Play", font);
	game.setCharacterSize(50);
	game.setStyle(Text::Bold);
	game.setPosition(450, 420);

	credits = Text("Credits", font);
	credits.setCharacterSize(50);
	credits.setStyle(Text::Bold);
	credits.setPosition(450, 480);

	exit = Text("Exit", font);
	exit.setCharacterSize(50);
	exit.setStyle(Text::Bold);
	exit.setPosition(450, 540);


	if (actionPressed == false)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			selection--;

			actionPressed = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			selection++;

			actionPressed = true;
		}
	}

	if (actionPressed == true)
	{
		timer += dt.asSeconds();

		if (timer >= coolDown)
		{
			timer = 0;

			actionPressed = false;
		}
	}

	if (selection > lastOption)
	{
		selection = firstOption;
	}

	else if (selection < firstOption)
	{
		selection = lastOption;
	}

	switch (selection)
	{
	case Game:
		if (selection == Game)
		{
			game.setFillColor(Color::Red);

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				GameLoop();
			}
		}
		else
		{
			game.setFillColor(Color::White);
		}
		break;

	case Credits:
		if (selection == Credits)
		{
			credits.setFillColor(Color::Red);

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				DrawCredits();
			}
		}
		else
		{
			credits.setFillColor(Color::White);
		}
		break;

	case Exit:
		if (selection == Exit)
		{
			exit.setFillColor(Color::Red);

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				window->close();
			}
		}
		else
		{
			exit.setFillColor(Color::White);
		}
		break;
	}

	window->draw(menu);
	window->draw(game);
	window->draw(credits);
	window->draw(exit);
}

void GameManager::DrawCredits()
{
	bool escaped = false;

	while (!escaped)
	{
		credits = Text("Credits", font);
		credits.setCharacterSize(100);
		credits.setStyle(Text::Bold);
		credits.setFillColor(Color::White);
		credits.setPosition(400, 200);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			escaped;

			RunGame();
		}

		window->clear();
		window->draw(credits);
		window->display();
	}
}

void GameManager::GameLoop()
{
	float score = 0;

	bool collision = false;

	while (player->IsAlive(collision) == false)
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

	int selection = 0;

	float timer = 0;

	bool actionPressed = false;

	while (window->isOpen() /*&& player->IsAlive(collision) == false*/)
	{
		RestartClock();

		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		cout << timer << endl;

		window->clear();
		DrawMenu(selection, timer, actionPressed);
		window->display();
	}
}