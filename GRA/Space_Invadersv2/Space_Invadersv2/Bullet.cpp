#include "Bullet.h"



void Bullet::poruszanieBullet(int *Points, std::vector<sf::Sprite>& Enemy)
{
	
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
				*Points = *Points + 10;
				break;
			}

		}

	}
}


Bullet::Bullet()
{

}

Bullet::Bullet(sf::Vector2f wektor)
{
	sf::CircleShape kula(4); 
	kula.setFillColor(sf::Color(255, 180, 0));
	kula.setOutlineThickness(3);
	kula.setOutlineColor(sf::Color::Red);
	kula.setPosition(wektor.x, wektor.y);
	this->ShotedBulletPlayer.push_back(kula);
	

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



