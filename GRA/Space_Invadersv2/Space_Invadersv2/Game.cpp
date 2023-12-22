#include "Game.h"

Game::~Game()
{
	delete this-> MenuWindow;
	delete this->RenderMenuTexture;
	delete this->GameWindow;
	delete this->RenderGameTexture;
}

void Game::run()
{
	this->mainMenuShowing();
}



void Game::initMenuWindow()///Tworzenie Tekstow do menu i tekstury
{
	font.loadFromFile("Almendra-Regular.ttf");
	
	menuTexts[0].setString("Start Game");
	menuTexts[1].setString("Saves");
	menuTexts[2].setString("Options");
	menuTexts[3].setString("Exit");

	for (int i = 0; i < numMenuOptions; ++i) {
		menuTexts[i].setFont(font);
		menuTexts[i].setCharacterSize(24);
		menuTexts[i].setPosition(100.0f, 100.0f + i * 50.0f);
	}

	selectedOption = 0;
	menuTexts[selectedOption].setFillColor(sf::Color::Red);

	if (!RenderMenuTexture->create(static_cast<unsigned int>(MenuWindow->getSize().x), static_cast<unsigned int>(MenuWindow->getSize().y)))
	{
		std::cerr << "FAILED" << std::endl;
	}
	if (!MenuTexture.loadFromFile("galaxyMenu.png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}

	sprite.setTexture(MenuTexture,true);
}

void Game::mainMenuShowing()
{
	while (MenuWindow->isOpen())
	{
		RecznieEvents();

		RenderMenuTexture->clear(sf::Color::Black);

		MenuWindow->draw(sprite);

		for (int i = 0; i < numMenuOptions; ++i)
		{
			MenuWindow->draw(menuTexts[i]);
		}

		MenuWindow->display();
	}
}

void Game::RecznieEvents()
{
	sf::Event event;
	while (MenuWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			MenuWindow->close();
			break;

		case sf::Event::KeyPressed:
			ReczneWybieranie(event.key);
			break;

		default:
			break;
		}
	}
}

void Game::ReczneWybieranie(const sf::Event::KeyEvent& keyEvent)//Poruszanie siê strza³kami  po menu
{
	switch (keyEvent.code)
	{
	case sf::Keyboard::Up :
		Wybieranie(-1);
		break;

	case sf::Keyboard::Down:
		Wybieranie(1);
		break;

	case sf::Keyboard::Enter:
		ReczneWybieranieMenu();
		break;
	default :
		break;
	
	}
}

void Game::Wybieranie(int direction)
{
	menuTexts[selectedOption].setFillColor(sf::Color::White);
	selectedOption = (selectedOption + direction + numMenuOptions) % numMenuOptions;
	menuTexts[selectedOption].setFillColor(sf::Color::Red);
}

void Game::ReczneWybieranieMenu()///Gdzie ka¿da z opcji przekierowuje
{
	switch (selectedOption)
	{
	case 0:
		StartGame();
		break ;

	case 1:
		Saves();
		break;

	case 2:
		showOption();
		break;

	case 3:
		MenuWindow->close();

	default:
		break;
	}
}

void Game::initGameWindow()
{
	this->GameWindow = new sf::RenderWindow(sf::VideoMode(1100, 850), "Galaktyczny atak", sf::Style::Close | sf::Style::Titlebar);
	this->RenderGameTexture = (new sf::RenderTexture());
	
	if (!RenderGameTexture->create(static_cast<unsigned int>(GameWindow->getSize().x), static_cast<unsigned int>(GameWindow->getSize().y)))
	{
		std::cerr << "FAILED" << std::endl;
	}
	if (!GameTexture.loadFromFile("Gamegalaxy.png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}

	spriteGame.setTexture(GameTexture, true);
	spriteGame.scale(1.7f, 1.5f);
}

void Game::GamePollEvents()
{

		sf::Event e;
		while (this->GameWindow->pollEvent(e))
		{
			if (e.Event::type == sf::Event::Closed)
			{
				this->GameWindow->close();
			}
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
				this->GameWindow->close();
		}
}

void Game::StartGame()
{
	this->MenuWindow->close();
	initGameWindow();
	RenderGameTexture->clear();
	while (GameWindow->isOpen())
	{
		GameWindow->draw(spriteGame);

		GameWindow->display();

		this->GamePollEvents();
	}
}

void Game::showOption()
{

}

void Game::Saves()
{
}
