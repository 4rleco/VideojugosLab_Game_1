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

	float height;
	float width;

	float thickness;

	float gravity;

	Vector2f speed;

	bool isOnFloor;

public:
	Player(RectangleShape rectangle, float initialPosX, float posX, float initialPosY,
		float posY, float height, float width, bool isOnFloor);
	Player();
	~Player();

	void CreatePlayer();

	int GetPosX();
	int GetPosY();

	int SetPosX(float posX);
	int SetPosY(float posY);

	bool IsOnFloor();

	Vector2f GetSpeed();

	RectangleShape ChangePosition();
};