#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Floor
{
private:
	RectangleShape rectangle;

	Color color;

	float initialPosX;
	float initialWidth;

	float posX;
	float posY;

	float width;
	float height;

	float thickness;

public:
	Floor();
	~Floor();

	void CreateFloor();

	RectangleShape GetFloorShape();

	float GetPosX();
	float GetPosY();

	void SetPosX(float speed);
	float SetWidth();

	float GetWidh();
	float GetHeight();

	void UpdateFloorPosition();

	void RestarPosition();

	void ResetFloor();
};