#pragma once
#include <vector>
#include "Enemy.h"
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include "Player.h"



struct zapisywanie
{
	std::string Name;
	int IlePunktow;

};

class Game
{
private:

	/// O OKNIE GRY
	sf::Text NazwaPlayer;
	std::string imie;
	bool wprowadzaneimie;
	int ilePlayer=0 ;

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

	///MENU W GRZE
	sf::Text howPlay;
	int wybranastop;
	bool wstrzymana = false;
	sf::RenderWindow* GameMenu;
	sf::Text Gamemenu[2];
	sf::Texture GameMenuTexture;
	sf::Sprite GameMenuSprite;
	

	///ANIMACJA WYBUCHU
	sf::Texture* WybuchT = new sf::Texture[8];
	sf::Sprite WybuchS;
	const float ilosc_klatek = 0.1f;
	int ktora_animacja=0;
	sf::Clock Czas;
	

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
	int ileSpawnedEnemy = 60;


	///Lista Wynikow
	zapisywanie* Gracze = new zapisywanie[1]; 
	std::vector<std::string> Nazwy;
	std::vector<int> Punkty;
	sf::Text Imiona[5];
	sf::Text PunktyGraczy[5];
	sf::Text SaveTexts[3];
	

	/// O ENEMYS
	Enemy enemy;


	/// O MENU GLOWNYM I GWIAZDKA

	sf::ConvexShape gwiazdka;
	int liczbaWierzcho³ków = 6;
	sf::ConvexShape tablicaGwiazd[5];
	float katWewn = 20.f;
	float katzwene = 50.f;
	float kat;
	float x, y;
	float katRamienia;


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
	

	///GAME OVER i WIN
	sf::Text OVER[2];
	
	int wybranaover;
	sf::Texture GameOverT;
	sf::Sprite GameOverS;

	sf::Texture winT;
	sf::Sprite winS;



public:
	Game();
	virtual ~Game();
	

	void zapisPlayer();
	void odzczytPlayer();
	zapisywanie* zwiekszTablice(zapisywanie* staraTablica);

	void stop();
	void stop1(const sf::Event::KeyEvent& keyEvent);
	void stop2(int direction);
	void stop3();


	void GameOver();
	void over1(const sf::Event::KeyEvent& keyEvent);
	void over2(int direction);
	void over3();

	void WinGame();

	void initTexture();

	void showOption();

	void Autor();

	void StartGame();
	bool czyresetowany = false;
	///PODAWANIE NAZWY GRACZA
	void PodawanieImienie();
	void rysowanieImienia();

	///UTWORZENIE OKNA GRY
	void initGameWindow();
	void GamePollEvents();

	///MENU GLOWNE I JEGO KONSTRUKCJA
	void gwiazda();

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

	void resetowanieUstawien();

	void animacja(sf::Sprite gracz);
	void initanimacion();
	

	///RYSOWANIE
	void renderHealth();

	void renderScore();
	
	void render();

	///AKTUALIZACJA STANU GRY
	
	void update();
	

};





