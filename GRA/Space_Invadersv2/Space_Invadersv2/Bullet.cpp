#include "Bullet.h"


sf::Sprite Bullet::getSprite() const
{
	return sf::Sprite(BulletS);
}

int Bullet::PointsBack()
{
	return Punkty;
}

void Bullet::poruszanieBullet(int Points, std::vector<sf::Sprite>& Enemy)
{
	Punkty = Points;
	
	for (int i = 0; i < ShotedBulletPlayer.size(); i++)
	{
		ShotedBulletPlayer[i].move(0, BulletSpeed);

		if (ShotedBulletPlayer[i].getPosition().y < 2.f)
		{
			ShotedBulletPlayer.erase(ShotedBulletPlayer.begin() + i);
			continue;
		}

		for (int j = 0; j < Enemy.size(); j++)
		{
			if (ShotedBulletPlayer[i].getGlobalBounds().intersects(Enemy[j].getGlobalBounds()))
			{
				ShotedBulletPlayer.erase(ShotedBulletPlayer.begin() + i);
				Enemy.erase(Enemy.begin() + j);
				Punkty = Punkty + 10;
				break;
			}

		}

	}
}


Bullet::Bullet()
{

}

Bullet::Bullet(sf::Vector2f wektor,sf::Texture pociskT)
{
	this->BulletS.setTexture(pociskT);

	this->BulletS.scale(0.7, 0.7);
	this->BulletS.setPosition(wektor.x, wektor.y);
	this->ShotedBulletPlayer.push_back(BulletS);

}

void Bullet::renderBullet(sf::RenderWindow* window)
{
	for(auto& e: ShotedBulletPlayer)
	{
		window->draw(e);
	}
	
}



Bullet::~Bullet()
{

}



