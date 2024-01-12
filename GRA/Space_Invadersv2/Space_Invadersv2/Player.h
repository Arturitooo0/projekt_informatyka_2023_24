#pragma once
#include "Bullet.h"


class Player
{
private:
	int recoil;
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	//SPEED
	float speed = 14;


	
public:
	Player();
	~Player();
	void odejmujrecoil();
	void setPlayerPosition();
	int getRecoil();


	sf::Vector2f GetPlayerPosition();
	sf::Sprite GetPlayer();
	std::vector<Bullet> ShotedBullet;
	void renderPlayer(sf::RenderWindow* window);
	void initPlayer();
	
	void PoruszaniePlayer();

};

