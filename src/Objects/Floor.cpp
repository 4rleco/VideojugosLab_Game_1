#include "Floor.h"

Floor::Floor()
{
	this->rectangle = RectangleShape();
	this->color = Color::Red;

	this->initialPosX = 0.0f;
	this->initialWidth = 1080.0f;

	this->posX = initialPosX;
	this->posY = 680.0f;

	this->width = initialWidth;
	this->height = 20.0f;

	this->thickness = 5;
}

Floor::~Floor()
{
	cout << "The floor has been eliminated!" << endl;
}

void Floor::CreateFloor()
{
	rectangle.setSize(Vector2f(width, height));
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(thickness);
	rectangle.setPosition(posX, posY);
}

RectangleShape Floor::GetFloorShape()
{
	return rectangle;
}

float Floor::GetPosX()
{
	return posX;
}

float Floor::GetPosY()
{
	return posY;
}

void Floor::SetPosX(float speed)
{
	this->posX -= speed;
}

float Floor::SetWidth()
{
	do
	{
		width = rand() % 720 + 100;

	} while (width > 720);

	return posY;
}

float Floor::GetWidh()
{
	return width;
}

float Floor::GetHeight()
{
	return height;
}

void Floor::UpdateFloorPosition()
{
	rectangle.setPosition(posX, posY);
}

void Floor::RestarPosition()
{
	if (posX + width < 0)
	{
		posX = 1100;

		SetWidth();

		rectangle.setSize(Vector2f(width, height));
	}
}

void Floor::ResetFloor()
{
	posX = initialPosX;
	width = initialWidth;
}