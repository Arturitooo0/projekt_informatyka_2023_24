#pragma once
#include<SFML/Graphics.hpp>
#include "Bullet.h"

#include <iostream>
class Enemy
{
private:
	sf::Texture EnemyT[4];
	sf::Sprite EnemyS[4];
	std::vector<sf::Sprite> EnemySprites;
	std::vector<sf::Sprite> SpawnedEnemys;
	int type;
	float x;
	
	float EnemySpeed;
	int maxEnemy ;

public:
	Enemy();
	~Enemy();
	
	Bullet pocisk;
	std::vector<sf::Sprite> &getEnemy();
	void RenderEnemy(sf::RenderWindow* window);
	void initEnemys();
	void SpawnEnemy(float x);
	void PoruszanieEnemy(int poziom_trudnosci,int *ilespawnedenemy, int *Points, int *Health,sf::Sprite Player);
};

