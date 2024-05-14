#include "GameManager.h"

int main()
{
	RenderWindow window;

	GameManager gameManager = GameManager(&window);

	gameManager.RunGame();

	return 0;
}