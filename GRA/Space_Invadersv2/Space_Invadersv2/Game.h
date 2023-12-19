#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow* window;
	void initWindow();
	void initTexture();
	void mainMenu();
	void initPlayer();
	

public:
	Game();
	virtual ~Game();
	void run();
	void render();
	void update();
	

};

