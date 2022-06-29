#include <iostream>
#include <string>

#include "Game.h"

int main()
{
	Game* game = new Game();
	game->Start();

	delete game;
	return 0;
}
