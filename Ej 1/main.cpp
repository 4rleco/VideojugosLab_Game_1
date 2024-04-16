#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	Clock clock;

	Time dt;

	float rectangleX = 120.0f;	
	float rectangleY = 20.0f;	

	RenderWindow window(VideoMode(1080, 720), "SFML works!");

	RectangleShape rectangle;
	rectangle.setSize(Vector2f(100, 50));
	rectangle.setOutlineColor(Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(rectangleX, rectangleY);

	while (window.isOpen())
	{
		dt = clock.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{			
			rectangleX += 100.0f * dt.asSeconds();			
			rectangle.setPosition(rectangleX, rectangleY);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			rectangleY -= 50.0f * dt.asSeconds();			
			rectangle.setPosition(rectangleX, rectangleY);
		}

		window.clear();
		window.draw(rectangle);
		window.display();
	}

	return 0;
}