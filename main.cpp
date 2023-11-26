#include <iostream>
#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;
	//Petla gry
	while (game.running() && !game.getEndGame())
	{

		game.update();

		game.render();

	}

	return 0;
}