#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
private:

	
	sf::Sprite BulletS;
	std::vector<sf::Sprite> ShotedBulletPlayer;
	float BulletSpeed = -0.1;
	int Punkty;

	
public:
	

	Bullet();
	Bullet(sf::Vector2f,sf::Texture pociskT);
	void renderBullet(sf::RenderWindow* window);
	int PointsBack();
	sf::Sprite getSprite() const;
	void poruszanieBullet(int Points, std::vector<sf::Sprite>& Enemy);
	void initBullet(sf::Vector2f,sf::Texture BulletT);
	~Bullet();

};

