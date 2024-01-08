#include "Enemy.h"

Enemy::Enemy()
{
	this->initEnemys();
}

Enemy::~Enemy()
{

}

void Enemy::initEnemys()
{
	

	std::string  filename;

	for (int i = 1; i < 5; i++)
	{

		filename = "wrog" + std::to_string(i) + ".png";
		if (!EnemyT[i - 1].loadFromFile(filename))
		{
			std::cerr << "FAILED LOADING" << std::endl;
		}

		EnemyS[i - 1].setTexture(EnemyT[i - 1], true);
		EnemyS[i - 1].scale(0.5f, 0.5f);

		EnemySprites.push_back(EnemyS[i - 1]);
	}
}


void Enemy::SpawnEnemy(float x)
{
	type = rand() % 4;


	switch (type)
	{
	case 0:
		this->EnemySprites[0].setPosition(x, 30.0f);
		break;
	case 1:
		this->EnemySprites[1].setPosition(x, 30.0f);
		break;
	case 2:
		this->EnemySprites[2].setPosition(x, 30.0f);
		break;
	case 3:
		this->EnemySprites[3].setPosition(x, 30.0f);
		break;
	}
	SpawnedEnemys.push_back(EnemySprites[type]);
}

void Enemy::PoruszanieEnemy(int poziom_trudnosci, int Points,int Health,sf::Sprite Player)
{
	Punkty = Points+ pocisk.PointsBack() ;
	Zdrowie = Health;
	if (poziom_trudnosci == 1)
	{
		EnemySpeed = 0.1;//0.1
		maxEnemy = 4;

	}

	if (poziom_trudnosci == 2)
	{
		EnemySpeed = 0.2;//0.2
		maxEnemy = 6;

	}

	if (SpawnedEnemys.size() < maxEnemy && Wygrana >0)
	{
		x += 100;
		if (x > 800)
			x = 0;
		SpawnEnemy(x);
		Wygrana--;
	}
	for (int i = 0; i < SpawnedEnemys.size(); i++)
	{
		SpawnedEnemys[i].move(0, EnemySpeed);
		if (SpawnedEnemys[i].getPosition().y > 950)
		{
			x = SpawnedEnemys[i].getPosition().x;
			this->SpawnedEnemys.erase(SpawnedEnemys.begin() + i);
			Punkty = Punkty - 5;
		}

		if (SpawnedEnemys[i].getGlobalBounds().intersects(Player.getGlobalBounds()))
		{
			Zdrowie--;
			this->SpawnedEnemys.erase(SpawnedEnemys.begin() + i);
			Punkty = Punkty +10;
		}
	}
}

int Enemy::Czywygrana()
{
	return Wygrana;
}

std::vector<sf::Sprite>& Enemy::getEnemy()
{
	return SpawnedEnemys;
}

int Enemy::GetPoints()
{
	return Punkty;
}

int Enemy::GetHealth()
{
	return Zdrowie;
}

void Enemy::RenderEnemy(sf::RenderWindow* window)
{
	for (auto& e : SpawnedEnemys)
	{
		window->draw(e);
	}
}