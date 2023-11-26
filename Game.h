#pragma once
#include<iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game
{
private:
	//Okno
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Pozycja myszki w oknie
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//logika
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool endgame;

	//Obiekty w grze
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Prywatne funkcje
	void initVariables();
	void initWIndow();
	void initEnemies();

public:
	//konstruktory , destruktory
	Game();
	virtual ~Game();

	//Zezwolenia
	const bool running() const;
	const bool getEndGame()const;

	//Funkcje
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();

	void renderEnemies();
	void render();
};
