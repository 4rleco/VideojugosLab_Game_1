#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Obstacle
{
private:

	RectangleShape rectangle;

	Color color;

	float initialPosX;

	float posX;
	float posY;

	float width;
	float height;

	float thickness;

public:
	Obstacle();
	~Obstacle();

	void CreateObstacle();

	RectangleShape GetObstacleShape();

	float GetPosX();
	float GetPosY();

	float GetWidh();
	float GetHeight();

	void SetPosX(float speed);
	float SetPosY();

	void UpdateObstaclePosition();

	void RestarPosiion();

	void ResetObstacle();
};