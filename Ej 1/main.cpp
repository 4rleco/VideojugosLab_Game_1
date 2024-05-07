#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

#include "GameManager.h"

using namespace sf;
using namespace std;

int main()
{
	Clock clock;

	Time dt;

	int screenWidth = 1080;
	int screenHeight = 720;

	RenderWindow window(VideoMode(screenWidth, screenHeight), "SFML works!");

	GameManager gameManager = GameManager(&window);



	float fwidth = screenWidth;
	float fheight = screenHeight;
	float FposX = 0.0f;
	float FposY = 680.0f;

	float initialPosX = 0.0f;	
	float posX = initialPosX;	
	float initialPosY = fheight - 70;	
	float posY = initialPosY;	

	float gravity = 20.0f;

	Vector2f speed(100.0f, 50.0f);

	bool isOnFloor = true;	

	RectangleShape floor;
	floor.setSize(Vector2f(fwidth,fheight));
	floor.setOutlineColor(Color::Red);
	floor.setOutlineThickness(5);
	floor.setPosition(FposX, FposY);
	
	gameManager.CreateGame();

	while (window.isOpen())
	{
		gameManager.RestartClock();

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		gameManager.PlayerMovement();

		/*if (Keyboard::isKeyPressed(Keyboard::D))
		{			
			posX += speed.x * dt.asSeconds();
			rectangle.setPosition(posX, posY);
		}

		if(Keyboard::isKeyPressed(Keyboard::A))
		{			
			posX -= speed.x * dt.asSeconds();
			rectangle.setPosition(posX, posY);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			posY -= speed.y * dt.asSeconds();
			rectangle.setPosition(posX, posY);
			isOnFloor = false;
		}

		if (isOnFloor == false)
		{
			posY += gravity * dt.asSeconds();

			rectangle.setPosition(posX, posY);

			if (posY >= initialPosY)
			{
				isOnFloor = true;
			}			
		}*/

		window.clear();
		window.draw(floor);
		gameManager.DrawGame();
		window.display();
	}

	return 0;
}