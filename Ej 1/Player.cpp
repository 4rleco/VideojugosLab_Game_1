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

	this->speed = Vector2f(100.0f, 50.0f);
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
	rectangle.setSize(Vector2f(width, height));
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

Vector2f Player::GetSpeed()
{
	return speed;
}

void Player::UpdatePosition(float& posX, float& posY)
{
	rectangle.setPosition(posX, posY);
}