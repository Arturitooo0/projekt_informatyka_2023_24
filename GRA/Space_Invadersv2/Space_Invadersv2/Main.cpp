#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


int main()
{
	srand(time(NULL));
	Game G1(sf::Vector2f(1200, 800));

	G1.run();

	return 0;
}