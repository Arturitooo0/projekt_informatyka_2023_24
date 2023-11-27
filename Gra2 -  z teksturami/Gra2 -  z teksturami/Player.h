#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:

public:
	Player();
	virtual ~Player();

	void render(sf::RenderTarget& target);
	void update();
};

