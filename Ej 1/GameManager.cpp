#include "GameManager.h"

GameManager::GameManager(RenderWindow* window)
{
	this->clock = Clock();
	this->dt = Time();
	this->font = Font();
	this->text = Text();
	this->window = window;

	this->screenWidth = 1080;
	this->screenHeight = 720;

	this->player = new Player(screenWidth / 4, screenWidth / 4, 650.0f, 650.0f, 50.0f, 100.0f);

	this->obstacle = Obstacle::Obstacle();

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

		if (playerPosY >= 650.0f)
		{
			grounded = true;
		}
	}
}

void GameManager::Score(float& score)
{
	score += dt.asSeconds();	

	cout << score << endl;
}

void GameManager::ScoreText(int score)
{
	string score_txt = "Score " + to_string(score);

	text = Text(score_txt, font);
	text.setCharacterSize(20);
	text.setStyle(Text::Bold);
	text.setFillColor(Color::Yellow);
	text.setPosition(800.0f, 2.0f);
}

void GameManager::ObstacleMovement()
{
	float speed = 100.0f;

	speed *= dt.asSeconds();

	obstacle.SetPosX(speed);

	obstacle.UpdateObstaclePosition();

	obstacle.RestarPosiion();
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

void GameManager::DrawGame()
{
	window->draw(player->GetPlayerShape());

	window->draw(obstacle.GetObstacleShape());

	window->draw(text);
}

void GameManager::InitGame(RectangleShape& floor)
{
	window = new RenderWindow(VideoMode(screenWidth, screenHeight), "SideScroller");

	font.loadFromFile("font/arial.ttf");

	float fwidth = screenWidth;
	float fheight = screenHeight;
	float FposX = 0.0f;
	float FposY = 680.0f;

	floor.setSize(Vector2f(fwidth, fheight));
	floor.setOutlineColor(Color::Red);
	floor.setOutlineThickness(5);
	floor.setPosition(FposX, FposY);

	StartRand();

	CreateGame();
}

void GameManager::RunGame()
{
	RectangleShape floor;

	InitGame(floor);

	float score = 0;

	bool PlayerObstacleCollide = false;

	while (window->isOpen() && player->IsAlive(PlayerObstacleCollide) == false)
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

		Score(score);

		ScoreText(score);

		PlayerNObstacleCollision(PlayerObstacleCollide);

		window->clear();
		window->draw(floor);
		DrawGame();
		window->display();
	}
}