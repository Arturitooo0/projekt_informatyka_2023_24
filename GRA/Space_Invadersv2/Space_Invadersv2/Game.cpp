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

	Menusprite.setTexture(MenuTexture,true);
}

void Game::mainMenuShowing()
{
	while (MenuWindow->isOpen())
	{
		RecznieEvents();

		RenderMenuTexture->clear(sf::Color::Black);

		MenuWindow->draw(Menusprite);

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

void Game::initPlayer()
{
	if (!this->PlayerTexture.loadFromFile("statek_mysliwiec .png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}

	this->PlayerSprite.setTexture(this->PlayerTexture, true);
	this->PlayerSprite.scale(0.24f, 0.24f);
	this->PlayerSprite.setPosition(380, 860);
}

void Game::PoruszaniePlayer()
{
	this->movementSpeedPlayer = 12.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if(PlayerSprite.getPosition().x + 10.0f < 800.0f)
			PlayerSprite.move(movementSpeedPlayer, 0);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (PlayerSprite.getPosition().x - 10.0f > -70.0f)
			PlayerSprite.move(-movementSpeedPlayer,0);
		
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (PlayerSprite.getPosition().y - 10.0f >= 0.0f)
			PlayerSprite.move(0, -movementSpeedPlayer);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (PlayerSprite.getPosition().y + 10.0f <= 850.0f)
			PlayerSprite.move(0,movementSpeedPlayer);
	}

}

void Game::initEnemys()
{
	std::string  filename;
	for (int i = 1; i < 5; i++)
	{

		filename = "wrog" + std::to_string(i) + ".png";
		if (!EnemyT[i - 1].loadFromFile(filename))
		{
			std::cerr << "FAILED LOADING" << std::endl;
		}

		EnemyS[i - 1].setTexture(EnemyT[i - 1], true);
		if (i != 3 && i!= 4)
			EnemyS[i-1].scale(0.16f, 0.16f);

		EnemySprites.push_back(EnemyS[i-1]);
	}

	EnemySprites[3].setRotation(180);
	EnemySprites[2].scale(0.5, 0.5);
	EnemySprites[3].scale(0.06, 0.06);
	
		
		
}

void Game::SpawnEnemy()
{
	
	 type = rand() % 4;
	 x = static_cast<float> ((rand() % static_cast<int> (750))+70);


	switch (type)
	{
	case 0:
		this->EnemySprites[0].setPosition(x, 30.0f);
		break;
	case 1:
		this->EnemySprites[1].setPosition(x, 30.0f);
		break;
	case 2:
		this->EnemySprites[2].setPosition(x, 30.0f);
		break;
	case 3:
		this->EnemySprites[3].setPosition(x, 30.0f);
		break;
	}
	SpawnedEnemys.push_back(EnemySprites[type]);
}

void Game::PoruszanieEnemy()
{
	int maxEnemy = 6;
	if (SpawnedEnemys.size() < maxEnemy)
	{
		SpawnEnemy();
	}

	for (int i = 0; i < SpawnedEnemys.size(); i++)
	{
		SpawnedEnemys[i].move(0, 7.0f);
		if (SpawnedEnemys[i].getPosition().y > 950)
		{
			this->SpawnedEnemys.erase(SpawnedEnemys.begin()+i);
		}
	}

	

	

}

void Game::initGameWindow()
{
	this->GameWindow = new sf::RenderWindow(sf::VideoMode(950, 1000), "Galaktyczny atak", sf::Style::Close | sf::Style::Titlebar);
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
	initPlayer();
	initEnemys();
	while (GameWindow->isOpen())
	{
		PoruszaniePlayer();
		PoruszanieEnemy();
		this->RenderGameTexture->clear(sf::Color::Black);
		RenderGameTexture->draw(this->spriteGame);
		
		this->RenderGameTexture->display();

		GameWindow->clear();
		GameWindow->draw(sf::Sprite(RenderGameTexture->getTexture()));
		
		GameWindow->draw(sf::Sprite(PlayerSprite));
		
		for (auto& v : SpawnedEnemys)
		{
			GameWindow->draw(sf::Sprite(v));
		}
		
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
