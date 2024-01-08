#pragma once
#include "Bullet.h"

class Player
{
private:
	int recoil;
	sf::Texture BulletT;
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	int Punkty;
	//SPEED
	float speed = 0.3;
public:
	Player();
	~Player();
	void initBulletTExture();
	void odejmujrecoil();
	
	int GetPP();
	int getRecoil();
	sf::Vector2f GetPlayerPosition();
	sf::Sprite GetPlayer();
	std::vector<Bullet> ShotedBullet;
	void renderPlayer(sf::RenderWindow* window);
	void initPlayer();
	void PoruszaniePlayer();

};

