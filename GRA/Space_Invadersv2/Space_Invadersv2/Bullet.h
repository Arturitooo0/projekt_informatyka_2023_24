#pragma once
#include "Game.h"


class Bullet
{
private:
	sf::Sprite BulletSprite;
	
public:
	Bullet(float pozx, float pozy,const sf::Texture& textureBullet, std::vector<sf::Sprite> *wector);
	sf::Sprite getSprite() const;
	~Bullet();

};

