#include "Player.h"

Player::Player(RectangleShape rectangle, float initialPosX, float posX, float initialPosY,
	float posY, float height, float width, bool isOnFloor)
{
	this->rectangle = rectangle;

	this->color = Color::Blue;

	this->initialPosX = initialPosX;
	this->initialPosY =  initialPosY;

	this->posX = posX;
	this->posY = posY;

	this->height = height;
	this->width = width;

	this->thickness = 10;

	this->gravity = 20.0f;

	this->speed = Vector2f(100.0f, 50.0f);

	this->isOnFloor = isOnFloor;
}

Player::Player()
{

}

Player::~Player()
{
	cout << "The player has been destroyed" << endl;
}

void Player::CreatePlayer()
{
	rectangle.setSize(Vector2f(height, width));
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(thickness);
	rectangle.setPosition(initialPosX, initialPosY);
}

int Player::GetPosX()
{
	return posX;
}

int Player::GetPosY()
{
	return posY;
}

int Player::SetPosX(float posX)
{
	this->posX = posX;

	return this->posX;
}

int Player::SetPosY(float posY)
{
	this->posY = posY;

	return this->posY;
}

bool Player::IsOnFloor()
{
	return isOnFloor;
}

Vector2f Player::GetSpeed()
{
	return speed;
}

RectangleShape Player::ChangePosition()
{
	return rectangle.setPosition(posX, posY);
}