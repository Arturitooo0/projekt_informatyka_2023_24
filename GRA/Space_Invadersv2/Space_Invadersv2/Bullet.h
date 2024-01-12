#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
private:

	
	sf::CircleShape kula();
	float BulletSpeed = -14;

	
public:
	

	Bullet();
	std::vector<sf::CircleShape> ShotedBulletPlayer;
	Bullet(sf::Vector2f);
	
	void renderBullet(sf::RenderWindow* window);
	void poruszanieBullet(int *Points, std::vector<sf::Sprite>& Enemy);
	~Bullet();

};

