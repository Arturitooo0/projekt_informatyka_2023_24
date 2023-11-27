#pragma once
#include <SFML/Graphics.hpp>


class Game
{
private:
	sf::RenderWindow* window;
	void initWidnow();

public:
	Game();
	virtual ~Game();

	//finctions
	void update();
	void render();

	void run();
};

