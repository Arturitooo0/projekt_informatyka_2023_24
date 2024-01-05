#pragma once
#include <iostream>
#include <vector>
#include<SFML/Graphics.hpp>

#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "Bullet.h"

class Game
{
private:
	/// O OKNIE GRY
	void StartGame();
	void PodawanieImienie();
	void rysowanieImienia();
	sf::Text NazwaPlayer;
	std::string imie;


	sf::RenderWindow* GameWindow;
	sf::RenderTexture* RenderGameTexture;
	sf::Texture GameTexture;
	sf::Sprite spriteGame;
	void initGameWindow();
	void GamePollEvents();


	sf::Texture scoreT;
	sf::Sprite scoreS;
	sf::Texture serceT;
	sf::Sprite serceS;
	sf::Texture znaczekT;
	sf::Sprite znaczekS;

	//PUNKTY
	int Points=0;
	sf::Text Point;
	std::string PointString;

	//ZYCIE
	int Health;



	/// O PLAYER
	
	void initPlayer();
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	void PoruszaniePlayer();

	

	/// POCISK
	int resetowany;

	sf::Texture BulletTPlayer;
	sf::Sprite BulletSPlayer;
	
	std::vector<sf::Sprite> ShotedBulletPlayer;
	
	void poruszanieBullet();
	void initBullet();

	//SPEED
	float movementSpeedPlayer = 10;

	float BulletSpeed = -7;

	float EnemySpeed ;
	int maxEnemy=6;


	/// O ENEMYS
	
	void initEnemys();
	void SpawnEnemy(float x);
	void PoruszanieEnemy();
	sf::Texture EnemyT[4];
	sf::Sprite EnemyS[4];
	std::vector<sf::Sprite> EnemySprites;
	std::vector<sf::Sprite> SpawnedEnemys;
	int type;
	float x;


	/// O MENU GLOWNYM

	void initMenuWindow();
	void initTexture();
	sf::RenderWindow* MenuWindow;
	sf::RenderTexture* RenderMenuTexture;
	sf::Texture MenuTexture;
	sf::Font font;
	void mainMenuShowing();
	sf::Sprite Menusprite;
	void ReczneWybieranie(const sf::Event::KeyEvent& keyEvent);
	void ReczneWybieranieMenu();
	void Wybieranie(int direction);
	void RecznieEvents();
	sf::Text menuTexts[5];///4 STRINGI Z MENU
	int selectedOption; ///WYBRANA OPCJA W DANYM MOMENCIE
	const int numMenuOptions = 5;///OPCJE Z SWITCHA Z MENU

	//AUTOR
	void Autor();
	sf::Text Autortext[3];

	///POZIOM TRUDNOSCI
	void showOption();
	int poziom_trudnosci = 1;
	sf::Text tekst1;
	sf::Text tekst2;
	sf::Text MenuOptiontext[2];
	int wybranaopcja;
	void ReczneWybieranieOpcji_1(const sf::Event::KeyEvent& keyEvent);
	void ReczneWybieranieMenuOpcji_3();
	void WybieranieOpcji_2(int direction);
	
	//ZAPISY

	void Saves();
	

public:
	Game();
	Game(const sf::Vector2f& screenSize) : MenuWindow(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Space Invaders")), RenderMenuTexture(new sf::RenderTexture()) {
		initMenuWindow();

	}

	virtual ~Game();
	void run();
	void render();
	void update();
	

};

