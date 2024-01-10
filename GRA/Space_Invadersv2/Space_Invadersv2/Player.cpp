#include "Player.h"
#define DEFAULT_BULLET_RESET	7

Player::Player()
{
	initPlayer();
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

void Player::PoruszaniePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (PlayerSprite.getPosition().x + 10.0f < 870.0f)
			PlayerSprite.move(speed, 0);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (PlayerSprite.getPosition().x - 10.0f > 0.0f)
			PlayerSprite.move(-speed, 0);

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (PlayerSprite.getPosition().y - 10.0f >= 350.0f)
			PlayerSprite.move(0, -speed);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (PlayerSprite.getPosition().y + 10.0f <= 850.0f)
			PlayerSprite.move(0, speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && recoil==0)
	{
		
		Bullet pocisk(GetPlayerPosition());
		ShotedBullet.push_back(pocisk);
		
		recoil = DEFAULT_BULLET_RESET;
	}
	
}


void Player::setPlayerPosition()
{
	PlayerSprite.setPosition(380, 860);
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