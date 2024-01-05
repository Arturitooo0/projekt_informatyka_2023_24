#include "Game.h"
#define DEFAULT_BULLET_RESET	5


Game::~Game()
{
	delete this-> MenuWindow;
	delete this->RenderMenuTexture;
	delete this->GameWindow;
	delete this->RenderGameTexture;
}

Game::Game()
{

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
	menuTexts[3].setString("Autor");
	menuTexts[4].setString("Exit");

	for (int i = 0; i < numMenuOptions; ++i) {
		menuTexts[i].setFont(font);
		menuTexts[i].setCharacterSize(24);
		menuTexts[i].setPosition(100.0f, 100.0f + i * 60.0f);
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
		Autor();
		break;
	case 4:
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
	;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && resetowany ==0)
	{
		Bullet pocisk(PlayerSprite.getPosition().x+35 , PlayerSprite.getPosition().y + 15, BulletTPlayer,&ShotedBulletPlayer);
		this->resetowany = DEFAULT_BULLET_RESET;

	}
}

void Game::initBullet()
{
	if (!BulletTPlayer.loadFromFile("pocisk2.png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}

}

void Game::poruszanieBullet()
{
	for (int i = 0; i < ShotedBulletPlayer.size(); i++)
	{
		ShotedBulletPlayer[i].move(0, BulletSpeed);

		if (ShotedBulletPlayer[i].getPosition().y < 2.f)
		{
			ShotedBulletPlayer.erase(ShotedBulletPlayer.begin() + i);
			continue;
		}
	
		for (int j = 0; j < SpawnedEnemys.size(); j++)
		{
			if (ShotedBulletPlayer[i].getGlobalBounds().intersects(SpawnedEnemys[j].getGlobalBounds()))
			{
				ShotedBulletPlayer.erase(ShotedBulletPlayer.begin() + i);
				SpawnedEnemys.erase(SpawnedEnemys.begin() + j);
				Points = Points+10;
				break;
			}
			
		}
		
	}
}

void Game::initEnemys()
{
	std::string  filename;

	if (poziom_trudnosci == 1)
	{
		EnemySpeed = 7;//0.1
		 maxEnemy = 4;
		 Health = 4;
	}

	if (poziom_trudnosci == 2)
	{
		EnemySpeed = 9;//0.2
		maxEnemy = 6;
		Health = 2;
	}
	for (int i = 1; i < 5; i++)
	{

		filename = "wrog" + std::to_string(i) + ".png";
		if (!EnemyT[i - 1].loadFromFile(filename))
		{
			std::cerr << "FAILED LOADING" << std::endl;
		}

		EnemyS[i - 1].setTexture(EnemyT[i - 1], true);
		EnemyS[i-1].scale(0.5f, 0.5f);

		EnemySprites.push_back(EnemyS[i-1]);
	}	
}

void Game::SpawnEnemy(float x)
{
	
	 type = rand() % 4;


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
	if (SpawnedEnemys.size() < maxEnemy)
	{
		x += 100;
		if (x > 800 )
			x = 0;
		SpawnEnemy(x);
	}
	for (int i = 0; i < SpawnedEnemys.size(); i++)
	{
		SpawnedEnemys[i].move(0, EnemySpeed);
		if (SpawnedEnemys[i].getPosition().y > 950)
		{
			x = SpawnedEnemys[i].getPosition().x;
			this->SpawnedEnemys.erase(SpawnedEnemys.begin()+i);
			Points = Points - 5;
		}

		if (SpawnedEnemys[i].getGlobalBounds().intersects(PlayerSprite.getGlobalBounds()))
		{
			Health--;
			this->SpawnedEnemys.erase(SpawnedEnemys.begin() + i);
			Points = Points + 10;
		}
	}
}

void Game::initGameWindow()
{
	this->GameWindow = new sf::RenderWindow(sf::VideoMode(950, 1000), "", sf::Style::Close | sf::Style::Titlebar);
	this->RenderGameTexture = (new sf::RenderTexture());
	
	if (!RenderGameTexture->create(static_cast<unsigned int>(GameWindow->getSize().x), static_cast<unsigned int>(GameWindow->getSize().y)))
	{
		std::cerr << "FAILED" << std::endl;
	}
	if(poziom_trudnosci==1){
		if (!GameTexture.loadFromFile("Gamegalaxy.png"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			spriteGame.setTexture(GameTexture, true);
			spriteGame.scale(1.7f, 1.5f);
	}

	if (poziom_trudnosci == 2) {
		if (!GameTexture.loadFromFile("galaxy2.jpg"))
		{
			std::cerr << "FAILED LOADING" << std::endl;
		}
		spriteGame.setTexture(GameTexture, true);
		spriteGame.scale(1.f, 1.f);
	}
	

	if (!znaczekT.loadFromFile("space.png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}
	znaczekS.setTexture(znaczekT, true);
	znaczekS.setPosition(350, 2);
	znaczekS.scale(0.7, 0.7);

	if (!serceT.loadFromFile("serce.png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}
	serceS.setTexture(serceT, true);
	serceS.scale(1.2, 1.2);

	if (!scoreT.loadFromFile("score.png"))
	{
		std::cerr << "FAILED LOADING" << std::endl;
	}
	scoreS.setTexture(scoreT, true);
	scoreS.setPosition(820, 8);
	scoreS.scale(0.7, 0.7);
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
	rysowanieImienia();

	font.loadFromFile("Arial.ttf");
	this->MenuWindow->close();
	
	initGameWindow();
	initPlayer();
	initBullet();
	initEnemys();

	while (GameWindow->isOpen())
	{
		
		if (resetowany > 0 )
		{
			resetowany--;
		}

		PoruszaniePlayer();
		PoruszanieEnemy();
		poruszanieBullet();
		this->RenderGameTexture->clear(sf::Color::Black);
		RenderGameTexture->draw(this->spriteGame);
		
		this->RenderGameTexture->display();

		GameWindow->clear();
		GameWindow->draw(sf::Sprite(RenderGameTexture->getTexture()));
		
		GameWindow->draw(scoreS);
		PointString = std::to_string(Points);
		Point.setString(PointString);
		Point.setPosition(860, 35);
		Point.setFont(font);
		Point.setCharacterSize(60);
		Point.setCharacterSize(27);
		Point.setFillColor(sf::Color::Yellow);
		GameWindow->draw(Point);

		GameWindow->draw(znaczekS);
		for (int p = 0; p < Health; p++)
		{
			serceS.setPosition(5 + 40 * p, 20);
			GameWindow->draw(serceS);
		}
		GameWindow->draw(sf::Sprite(PlayerSprite));

		for (auto& w : ShotedBulletPlayer)
		{
			GameWindow->draw(sf::Sprite(w));
		}
		
		for (auto& v : SpawnedEnemys)
		{
			GameWindow->draw(sf::Sprite(v));
		}


		GameWindow->display();
		
		this->GamePollEvents();
	}
	
}

void Game::PodawanieImienie()
{
	

	
	NazwaPlayer.setFont(font);
	NazwaPlayer.setCharacterSize(24);
	NazwaPlayer.setPosition(300.f, 300.f);
	NazwaPlayer.setFillColor(sf::Color::White);

	int wprowadzaneimie = 0;

	while (!wprowadzaneimie)
	{
		sf::Event event;
		while (MenuWindow->pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					imie += static_cast<char>(event.text.unicode);
					NazwaPlayer.setString("Player name : " + imie);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					wprowadzaneimie = 1;
				}
			}
		}
	}

}

void Game::rysowanieImienia()
{
	while (MenuWindow->isOpen())
	{
		RenderMenuTexture->clear(sf::Color::Black);
		MenuWindow->draw(Menusprite);
		PodawanieImienie();
		MenuWindow->draw(NazwaPlayer);
		MenuWindow->display();
	}
}


void Game::Autor()
{
	
	RenderMenuTexture->clear(sf::Color::Black);
	MenuWindow->draw(Menusprite);

	Autortext[0].setString("- Artur Wesierski -");
	Autortext[1].setString(" ARISS (3 sem) Grupa 5 ");
	Autortext[2].setString(" PRESS [ESC] TO BACK TO MENU");

	for (int i = 0; i < 3; ++i) {
		Autortext[i].setFont(font);
		Autortext[i].setCharacterSize(24);
		Autortext[i].setPosition(100.0f, 259.0f + i * 60.0f);
		Autortext[i].setFillColor(sf::Color::White);
	}
	Autortext[2].setCharacterSize(20);
	sf::Event e;
	while(MenuWindow->isOpen())
	{
		

		RenderMenuTexture->clear(sf::Color::Black);

		MenuWindow->draw(Menusprite);

		for (int i = 0; i < 3; ++i)
		{
			MenuWindow->draw(Autortext[i]);
		}

		MenuWindow->display();


		while (this->MenuWindow->pollEvent(e))
		{
			if (e.Event::type == sf::Event::Closed)
			{
				this->MenuWindow ->close();
			}
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
				this->mainMenuShowing();
		}
	}
}

void Game::showOption()
{
	RenderMenuTexture->clear(sf::Color::Black);
	MenuWindow->draw(Menusprite);

	tekst1.setString("Choose the difficulty level : ");
	tekst2.setString(" [ CONFIRM BY PRESSING ENTER ] ");
	MenuOptiontext[0].setString(" NOVICE ");
	MenuOptiontext[1].setString(" ADVANCED ");

	tekst1.setFont(font);
	tekst1.setCharacterSize(24);
	tekst1.setFillColor(sf::Color::White);

	tekst2.setFont(font);
	tekst2.setCharacterSize(20);
	tekst2.setFillColor(sf::Color::White);
	for (int i = 0; i < 2; ++i) {
		MenuOptiontext[i].setFont(font);
		MenuOptiontext[i].setCharacterSize(24);
		MenuOptiontext[i].setFillColor(sf::Color::White);
	}
	MenuOptiontext[wybranaopcja].setFillColor(sf::Color::Red);
	tekst1.setPosition(830.0f, 400);
	tekst2.setPosition(810.0f, 450);
	MenuOptiontext[0].setPosition(850.0f, 500);
	MenuOptiontext[1].setPosition(950.0f, 500);



	sf::Event e;
	while (MenuWindow->isOpen())
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
				ReczneWybieranieOpcji_1(event.key);
				break;

			default:
				break;
			}
		}
	

		RenderMenuTexture->clear(sf::Color::Black);

		MenuWindow->draw(Menusprite);

		for (int i = 0; i < 2; ++i)
		{
			MenuWindow->draw(tekst1);
			MenuWindow->draw(tekst2);
			MenuWindow->draw(MenuOptiontext[i]);
		}

		MenuWindow->display();

	}
}

void Game::ReczneWybieranieOpcji_1(const sf::Event::KeyEvent& keyEvent)
{
	switch (keyEvent.code)
	{
	case sf::Keyboard::Left:
		WybieranieOpcji_2(0);
		break;

	case sf::Keyboard::Right:
		WybieranieOpcji_2(1);
		break;

	case sf::Keyboard::Enter:
		ReczneWybieranieMenuOpcji_3();
		break;
	default:
		break;

	}
}

void Game::ReczneWybieranieMenuOpcji_3()
{
	switch (wybranaopcja)
	{
	case 0:
		this->poziom_trudnosci = 1;
		this->mainMenuShowing();
		break;
	case 1:
		this->poziom_trudnosci = 2;
		this->mainMenuShowing();
		break;
	default:
		break;

	}

}

void Game::WybieranieOpcji_2(int direction)
{
	MenuOptiontext[wybranaopcja].setFillColor(sf::Color::White);
	wybranaopcja =direction;
	MenuOptiontext[wybranaopcja].setFillColor(sf::Color::Red);

}

void Game::Saves()
{
}
