#include "Obstacle.h"

Obstacle::Obstacle()
{
	this->rectangle = RectangleShape();

	this->color = Color::Magenta;

	this->initialPosX = 1100;

	this->posX = initialPosX;
	this->posY = 0;

	this->height = 20.0f;
	this->width = 40.0f;

	this->thickness = 5.0f;
}

Obstacle::~Obstacle()
{
	cout << "An obstacle has been dstroyed" << endl;
}

float Obstacle::GetPosX()
{
	return posX;
}

float Obstacle::GetPosY()
{
	return posY;
}

float Obstacle::GetWidh()
{
	return width;
}

float Obstacle::GetHeight()
{
	return height;
}

void Obstacle::SetPosX(float speed)
{
	this->posX -= speed;
}

float Obstacle::SetPosY()
{
	do
	{
		posY = rand() % 680 + 50;

	} while (posY >= 720);

	cout << posY << endl;

	return posY;
}

RectangleShape Obstacle::GetObstacleShape()
{
	return rectangle;
}

void Obstacle::CreateObstacle()
{
	rectangle.setSize(Vector2f(width, height));
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(thickness);
	rectangle.setPosition(posX, SetPosY());
}

void Obstacle::UpdateObstaclePosition()
{
	rectangle.setPosition(posX, posY);
}

void Obstacle::RestarPosiion()
{
	if (posX + width < 0)
	{		
		posX = initialPosX;
		
		SetPosY();
	}
}