#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->event = Event();
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

	this->obstacle = Obstacle();
	this->obstacle1 = Obstacle();

	this->floor = Floor::Floor();

	this->grounded = true;

	this->isAlive = true;
}

GameManager::~GameManager()
{
	delete player;
	delete window;
}

void GameManager::CreateGame()
{
	this->player->CreatePlayer();

	obstacle.CreateObstacle();
	obstacle1.CreateObstacle();

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

	PlayerNFloorCollision(grounded);

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

void GameManager::ObstacleMovement(Obstacle& obstacle)
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

	int LeftScreenLimit = 0;

	speed *= dt.asSeconds();

	floor.SetPosX(speed);

	floor.UpdateFloorPosition();

	cout << floor.GetWidh() << endl;

	floor.RestarPosition();
}

bool GameManager::PlayerNObstacleCollision(Obstacle obstacle, bool& collision)
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

	else
	{
		return collision = false;
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
	window->draw(obstacle1.GetObstacleShape());

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

	int coolDown = 1;

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

void GameManager::DrawPause()
{
	Text pause;

	Text pause2;

	Text pause3;

	pause = Text("Pause", font);
	pause.setCharacterSize(100);
	pause.setStyle(Text::Bold);
	pause.setFillColor(Color::White);
	pause.setPosition(400, 100);


	pause2 = Text("Press e key to continue", font);
	pause2.setCharacterSize(20);
	pause2.setStyle(Text::Bold);
	pause2.setFillColor(Color::White);
	pause2.setPosition(420, 220);

	pause3 = Text("Press esc key to return to the menu", font);
	pause3.setCharacterSize(20);
	pause3.setStyle(Text::Bold);
	pause3.setFillColor(Color::White);
	pause3.setPosition(370, 280);

	window->draw(pause);
	window->draw(pause2);
	window->draw(pause3);
}

void GameManager::DrawDeath()
{
	Text death;

	Text death2;

	death = Text("You died", font);
	death.setCharacterSize(100);
	death.setStyle(Text::Bold);
	death.setFillColor(Color::Red);
	death.setPosition(300, 100);

	death2 = Text("press e key to return to the menu", font);
	death2.setCharacterSize(25);
	death2.setStyle(Text::Bold);
	death2.setFillColor(Color::Red);
	death2.setPosition(320, 400);

	score.setCharacterSize(50);
	score.setPosition(420.0f, 320.0f);

	window->draw(death);
	window->draw(death2);
}

void GameManager::DrawCredits()
{
	bool escaped = false;

	Text credits2;

	Text credits3;

	while (window->isOpen() && !escaped)
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		credits = Text("Game Made By", font);
		credits.setCharacterSize(80);
		credits.setStyle(Text::Bold);
		credits.setFillColor(Color::White);
		credits.setPosition(250, 200);

		credits2 = Text("Joaquin Herrero Ledner", font);
		credits2.setCharacterSize(40);
		credits2.setStyle(Text::Bold);
		credits2.setFillColor(Color::White);
		credits2.setPosition(300, 300);

		credits3 = Text("Pres esc key to return to the menu", font);
		credits3.setCharacterSize(30);
		credits3.setStyle(Text::Bold);
		credits3.setFillColor(Color::White);
		credits3.setPosition(270, 400);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			escaped = true;
		}

		window->clear();
		window->draw(credits);
		window->draw(credits2);
		window->draw(credits3);
		window->display();
	}
}

void GameManager::GameLoop()
{
	float score = 0;

	float timer = 0;

	int cooldown = 2;

	bool collision = false;

	bool pause = false;

	bool actionPressed = false;

	player->RestartPlayer();
	obstacle.ResetObstacle();
	obstacle1.ResetObstacle();
	floor.ResetFloor();

	while (window->isOpen() && player->IsAlive(collision) == false || pause == true)
	{
		RestartClock();

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		if (!pause)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pause = true;

				actionPressed = true;
			}

			PlayerMovement();

			ObstacleMovement(obstacle);
			ObstacleMovement(obstacle1);

			FloorMovement();

			Score(score);

			PlayerNObstacleCollision(obstacle, collision);
			PlayerNObstacleCollision(obstacle1, collision);

			PlayerFallsOfScreen(collision);
		}

		ScoreText(score);

		window->clear();

		if (pause == true && player->IsAlive(collision) == false)
		{
			DrawPause();
		}

		if (player->IsAlive(collision) == true)
		{
			pause = true;

			DrawDeath();
		}

		if (pause == true)
		{
			if (actionPressed == true)
			{
				timer += dt.asSeconds();

				if (timer >= cooldown)
				{
					timer = 0;

					actionPressed = false;
				}
			}

			if (actionPressed == false)
			{
				if (Keyboard::isKeyPressed(Keyboard::E))
				{
					pause = false;
				}

				else if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					return;
				}
			}
		}

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

	while (window->isOpen())
	{
		RestartClock();

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		window->clear();
		DrawMenu(selection, timer, actionPressed);
		window->display();
	}
}