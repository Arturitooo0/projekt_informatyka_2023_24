#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initTexture();
	this->mainMenu();
}


Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invaders");
}

void Game::mainMenu()
{

}

void Game::update()
{

}

void Game::render()
{
	this->window->clear();
	this->window->display();
}