#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow* MenuWindow;
	sf::RenderTexture* RenderMenuTexture;
	sf::Texture MenuTexture;
	sf::Font font;
	sf::RenderWindow* GameWindow;
	sf::RenderTexture* RenderGameTexture;
	sf::Texture GameTexture;
	sf::Sprite spriteGame;
	void initPlayer();
	void initGameWindow();
	void GamePollEvents();
	void Player();

	void initMenuWindow();
	void initTexture();
	void mainMenuShowing();
	sf::Sprite sprite;
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
	Game(const sf::Vector2f& screenSize) : MenuWindow(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Space Invaders")), RenderMenuTexture(new sf::RenderTexture()) {
		initMenuWindow();
	}

	virtual ~Game();
	void run();
	void render();
	void update();
	

};

