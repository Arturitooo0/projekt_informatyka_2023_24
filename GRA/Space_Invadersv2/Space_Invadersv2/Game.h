#pragma once
#include <vector>
#include "Enemy.h"
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "Player.h"

class Game
{
private:
	/// O OKNIE GRY
	sf::Text NazwaPlayer;
	std::string imie;

	sf::RenderWindow* GameWindow;
	sf::RenderTexture* RenderGameTexture;
	sf::Texture GameTexture;
	sf::Sprite spriteGame;
	

	///DODATKI NA EKRANIE GRY
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
	Player player;

	/// RECOIL POCISKU
	int resetowany;
	
	///END GAME
	bool endgame = false;


	/// O ENEMYS
	Enemy enemy;


	/// O MENU GLOWNYM
	sf::RenderWindow* MenuWindow;
	sf::RenderTexture* RenderMenuTexture;
	sf::Texture MenuTexture;
	sf::Font font;
	sf::Sprite Menusprite;
	sf::Text menuTexts[5];///4 STRINGI Z MENU
	int selectedOption; ///WYBRANA OPCJA W DANYM MOMENCIE
	const int numMenuOptions = 5;///OPCJE Z SWITCHA Z MENU

	//AUTOR
	sf::Text Autortext[3];

	///POZIOM TRUDNOSCI
	
	int poziom_trudnosci =1;
	sf::Text tekst1;
	sf::Text tekst2;
	sf::Text MenuOptiontext[2];
	int wybranaopcja;
	
	
	//ZAPISY

	void Saves();
	

public:
	Game();
	virtual ~Game();
	Game(const sf::Vector2f& screenSize) : MenuWindow(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Space Invaders")), RenderMenuTexture(new sf::RenderTexture()) {
		initMenuWindow();
	}



	void GameOver();

	void WinGame();

	void initTexture();

	void showOption();

	void Autor();

	void StartGame();

	///PODAWANIE NAZWY GRACZA
	void PodawanieImienie();
	void rysowanieImienia();

	///UTWORZENIE OKNA GRY
	void initGameWindow();
	void GamePollEvents();

	///MENU GLOWNE I JEGO KONSTRUKCJA
	void initMenuWindow();
	void mainMenuShowing();
	void ReczneWybieranieOpcji_1(const sf::Event::KeyEvent& keyEvent);
	void ReczneWybieranieMenuOpcji_3();
	void WybieranieOpcji_2(int direction);
	void ReczneWybieranie(const sf::Event::KeyEvent& keyEvent);
	void ReczneWybieranieMenu();
	void Wybieranie(int direction);
	void RecznieEvents();

	void run();

	///RYSOWANIE
	void renderHealth();

	void renderScore();
	
	void render();

	///AKTUALIZACJA STANU GRY
	
	void update();
	

};

