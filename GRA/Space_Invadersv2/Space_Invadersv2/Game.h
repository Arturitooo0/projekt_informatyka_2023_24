#pragma once
#include <iostream>
#include <vector>
#include<SFML/Graphics.hpp>
#include "windows.h"
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

class Game
{
private:
	/// O OKNIE GRY
	
	sf::RenderWindow* GameWindow;
	sf::RenderTexture* RenderGameTexture;
	sf::Texture GameTexture;
	sf::Sprite spriteGame;
	void initGameWindow();
	void GamePollEvents();


	/// O PLAYER
	
	void initPlayer();
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	void PoruszaniePlayer();
	int maxEnemy;
	float movementSpeedPlayer;


	/// O ENEMYS
	void initEnemys();
	void SpawnEnemy();
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
	sf::Text menuTexts[4];///4 STRINGI Z MENU
	int selectedOption; ///WYBRANA OPCJA W DANYM MOMENCIE
	const int numMenuOptions = 4;///OPCJE Z SWITCHA Z MENU
	void StartGame();
	void showOption();
	void Saves();
	

public:
	Game(){}
	Game(const sf::Vector2f& screenSize) : MenuWindow(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Space Invaders")), RenderMenuTexture(new sf::RenderTexture()) {
		initMenuWindow();
	}

	virtual ~Game();
	void run();
	void render();
	void update();
	

};

