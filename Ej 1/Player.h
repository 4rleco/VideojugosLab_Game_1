#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player
{
private:

	RectangleShape rectangle;

	Color color;

	float initialPosX;
	float initialPosY;

	float posX;
	float posY;

	float width;
	float height;

	float thickness;

	Vector2f speed;

	bool isAlive;

public:
	Player(float initialPosX, float posX, float initialPosY,
		float posY, float height, float width);
	~Player();

	RectangleShape GetPlayerShape();

	void CreatePlayer();

	float GetPosX();
	float GetPosY();

	float GetWidh();
	float GetHeight();

	void SetPosX(float posX);
	void SetPosY(float posY);

	Vector2f GetSpeed();

	void UpdatePosition(float& posX, float& posY);

	bool IsAlive(bool isAlive);
};