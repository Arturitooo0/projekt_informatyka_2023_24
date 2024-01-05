#include "Bullet.h"


sf::Sprite Bullet::getSprite() const
{
	return sf::Sprite(BulletSprite);
}

Bullet::Bullet(float pozx,float pozy,const sf::Texture& TextureBullet, std::vector<sf::Sprite> *wektor)
{
	this->BulletSprite.setTexture(TextureBullet);
	this->BulletSprite.scale(0.7, 0.7);
	this->BulletSprite.setPosition(pozx, pozy);
	wektor->push_back(BulletSprite);
}

Bullet::~Bullet()
{

}



