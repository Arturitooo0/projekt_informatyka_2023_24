#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
	delete this->window;
}

void Game::initWidnow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Game ", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}



void Game::run()
{
	while (window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::update()
{

	//pozwala zamekac okno i sprawdza czy to klikamy krzy¿yk lub ESC
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}

		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape);
		{
			this->window->close();
		}
	}
}

void Game::render()
{

	//Czysci ekran
	this->window->clear();


	//Rysuje wszystko
	this->window->display();


}
