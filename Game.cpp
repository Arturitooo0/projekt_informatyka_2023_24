#include "Game.h"

//Prywatne funkcje

void Game::initVariables()
{
	this->window = nullptr;
	//logika
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;  
	this->endgame = false;
}

void Game::initWIndow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	
	this->window = new sf::RenderWindow (this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);

}


void Game::initEnemies()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}
//Konstruktory , destruktory
Game::Game()
{
	this->initVariables();
	this->initWIndow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Zezwolenia
const bool Game::running()const
{
	return this->window->isOpen() ;
}

//funkcje

const bool Game::getEndGame() const
{
	return this->endgame;
}

void Game::spawnEnemy()
{
	//tworzenie i ustawianie pozycji i parametrow 
	this->enemy.setPosition(
		static_cast<float> (rand() % static_cast<int>
			(this->window->getSize().x - this->enemy.getSize().x)),
			0.f);

	int type = rand() % 5;

	switch (type)
	{
	case 0:
	{
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	}
	case 1:
	{
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	}
	case 2:
	{
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	}
	case 3:
	{
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	}
	case 4:
	{
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	}

	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}
	//Spawnowanie wrogow
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}


void Game::updateMousePositions()
{


	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Ruszanie enemies
	for (int i = 0; i<this->enemies.size();i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 5.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
	}



	//Sprawdzanie czy obiekt jest klikniety
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;
				bool deleted = false;

				for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
				{

					if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
					{
						//this->enemies.erase(this->enemies.begin() + 1);
						deleted = true;
						this->enemies.erase(this->enemies.begin() + i);

						//Ponits
						if(this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
						else if(this->enemies[i].getFillColor() == sf::Color::Blue)
							this->points += 7;
						else if (this->enemies[i].getFillColor() == sf::Color::Red)
							this->points += 3;
						else if (this->enemies[i].getFillColor() == sf::Color::Green)
							this->points += 1;
						else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
							this->points += 2;

						std::cout << "Points: " << this->points << "\n";

					}
				}

			}
			
		}
		else
		{
			this->mouseHeld = false;
		}
			
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endgame == false)
	{
		//Pozycja myszki

		this->updateMousePositions();

		this->updateEnemies();
	}
	///warunki konca gry
	if (this->health <= 0)
	{
		this->endgame = true;
	}

}

void Game::renderEnemies()
{
	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	this->window->clear();

	this->renderEnemies();

	this->window->display();
}
