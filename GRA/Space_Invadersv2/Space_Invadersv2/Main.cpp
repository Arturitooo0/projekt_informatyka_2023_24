
#include <iostream>
#include "Game.h"


int main()
{
	srand(time(NULL));
	Game G1(sf::Vector2f(1250, 700));

	G1.run();

	return 0;
}