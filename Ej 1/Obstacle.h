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

	float height;
	float width;

	float thickness;

public:
	Obstacle();
	~Obstacle();

	void CreateObstacle();

	RectangleShape GetObstacleShape();

	void SetPosX(float speed);
	float SetPosY();

	void UpdateObstaclePosition();

	void RestarPosiion();
};