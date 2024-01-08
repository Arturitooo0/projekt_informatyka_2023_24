#include "Player.h"
#define DEFAULT_BULLET_RESET	500

Player::Player()
{
	initPlayer();
	initBulletTExture();
}



void Player::odejmujrecoil()
{
	recoil--;
}

int Player::getRecoil()
{
	return recoil;
}

sf::Vector2f Player::GetPlayerPosition()
{

	return sf::Vector2f(PlayerSprite.getPosition().x+35, PlayerSprite.getPosition().y);
}


sf::Sprite Player::GetPlayer()
{
	return sf::Sprite(PlayerSprite);
}

void Player::renderPlayer(sf::RenderWindow* window )
{
	window->draw(PlayerSprite);
}


void Player::initBulletTExture()
{
	if (!BulletT.loadFromFile("pocisk2.png"))
	{
		std::cout << "FAILED LOADING" << std::endl;
	}
}

void Player::PoruszaniePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (PlayerSprite.getPosition().x + 10.0f < 800.0f)
			PlayerSprite.move(speed, 0);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (PlayerSprite.getPosition().x - 10.0f > -70.0f)
			PlayerSprite.move(-speed, 0);

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (PlayerSprite.getPosition().y - 10.0f >= 0.0f)
			PlayerSprite.move(0, -speed);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (PlayerSprite.getPosition().y + 10.0f <= 850.0f)
			PlayerSprite.move(0, speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && recoil==0)
	{
		Bullet pocisk(GetPlayerPosition(),BulletT);
		ShotedBullet.push_back(pocisk);
		
		recoil = DEFAULT_BULLET_RESET;
		Punkty = pocisk.PointsBack();

	}
	
}

int Player::GetPP()
{
	return Punkty;
}

void Player::initPlayer()
{

	if (!this->PlayerTexture.loadFromFile("statek_mysliwiec .png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}

	this->PlayerSprite.setTexture(this->PlayerTexture, true);
	this->PlayerSprite.scale(0.24f, 0.24f);
	this->PlayerSprite.setPosition(380, 860);
}

Player::~Player()
{
}