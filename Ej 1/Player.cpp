#include "Player.h"

Player::Player(float initialPosX, float posX, float initialPosY,
	float posY, float height, float width)
{
	this->rectangle = RectangleShape();

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

	this->isOnFloor = true;
}

Player::~Player()
{
	cout << "The player has been destroyed" << endl;
}

RectangleShape Player::GetPlayerShape()
{
	return rectangle;
}

void Player::CreatePlayer()
{
	rectangle.setSize(Vector2f(height, width));
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(thickness);
	rectangle.setPosition(initialPosX, initialPosY);
}

float Player::GetPosX()
{
	return posX;
}

float Player::GetPosY()
{
	return posY;
}

void Player::SetPosX(float posX)
{
	this->posX = posX;
}

void Player::SetPosY(float posY)
{
	this->posY = posY;
}

bool Player::IsOnFloor()
{
	return isOnFloor;
}

Vector2f Player::GetSpeed()
{
	return speed;
}

void Player::UpdatePosition(float& posX, float& posY)
{
	rectangle.setPosition(posX, posY);
}