#include "Game.h"


Game::Game()
{
	initMenuWindow();
}

void Game::run()
{
	this->mainMenuShowing();
}



void Game::resetowanieUstawien()
{
	
	Points = 0;
	enemy.getEnemy().clear();
	enemy.pocisk.ShotedBulletPlayer.clear();
	endgame = false;
	ileSpawnedEnemy = 50;
	player.ShotedBullet.clear();
	

}


///RYSOWANIE
void Game::render()
{
	this->RenderGameTexture->clear(sf::Color::Black);
	RenderGameTexture->draw(this->spriteGame);
	this->RenderGameTexture->display();

	GameWindow->clear();
	GameWindow->draw(sf::Sprite(RenderGameTexture->getTexture()));
	GameWindow->draw(znaczekS);
	renderScore();
	renderHealth();
	this->player.renderPlayer(GameWindow);
	this->enemy.RenderEnemy(GameWindow);
	for (auto& e : player.ShotedBullet)
	{
		e.renderBullet(GameWindow);
	}

}
void Game::renderHealth()
{
	for (int p = 0; p < Health; p++)
	{
		this->serceS.setPosition(5 + 40 * p, 20);
		this->GameWindow->draw(serceS);
	}
}
void Game::renderScore()
{
	this->GameWindow->draw(scoreS);
	this->PointString = std::to_string(Points);
	this->Point.setString(PointString);
	this->Point.setPosition(860, 35);
	this->Point.setFont(font);
	this->Point.setCharacterSize(60);
	this->Point.setCharacterSize(27);
	this->Point.setFillColor(sf::Color::Yellow);
	this->GameWindow->draw(this->Point);
}

///AKTUALIZOWANIE STANU GRY

void Game::update()
{
	if (endgame == false)
	{
		player.PoruszaniePlayer();
		for (auto& e : player.ShotedBullet)
		{
			e.poruszanieBullet(&Points, enemy.getEnemy());
		}
		enemy.PoruszanieEnemy(poziom_trudnosci,&ileSpawnedEnemy, &Points, &Health, player.GetPlayer());


		if (Health == 0 || (ileSpawnedEnemy ==0 && enemy.getEnemy().size()==0))
		{
			endgame = true;
			
		}

	}
	
	
}


///WSZYTSKO Z GLOWNYM MENU 
void Game::initMenuWindow()///Tworzenie Tekstow do menu i tekstury
{
	this->MenuWindow = new sf::RenderWindow(sf::VideoMode(1250, 700), "", sf::Style::Close | sf::Style::Titlebar);
	this->RenderMenuTexture = (new sf::RenderTexture());
	font.loadFromFile("Emulogic-zrEw.ttf");
	
	menuTexts[0].setString("Start Game");
	menuTexts[1].setString("Saves");
	menuTexts[2].setString("Options");
	menuTexts[3].setString("Autor");
	menuTexts[4].setString("Exit");

	for (int i = 0; i < numMenuOptions; ++i) {
		menuTexts[i].setFont(font);
		menuTexts[i].setCharacterSize(20);
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

///POD FUNKCJE MENU GLOWNEGO

void Game::Autor()
{

	RenderMenuTexture->clear(sf::Color::Black);
	MenuWindow->draw(Menusprite);

	Autortext[0].setString("- Artur Wesierski -");
	Autortext[1].setString(" ARISS (3 sem) Grupa 5 ");
	Autortext[2].setString(" PRESS [ESC] TO BACK TO MENU");

	for (int i = 0; i < 3; ++i) {
		Autortext[i].setFont(font);
		Autortext[i].setCharacterSize(20);
		Autortext[i].setPosition(100.0f, 259.0f + i * 60.0f);
		Autortext[i].setFillColor(sf::Color::White);
	}
	Autortext[2].setCharacterSize(18);
	sf::Event e;
	while (MenuWindow->isOpen())
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
				this->MenuWindow->close();
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
	tekst1.setCharacterSize(18);
	tekst1.setFillColor(sf::Color::White);

	tekst2.setFont(font);
	tekst2.setCharacterSize(15);
	tekst2.setFillColor(sf::Color::White);
	for (int i = 0; i < 2; ++i) {
		MenuOptiontext[i].setFont(font);
		MenuOptiontext[i].setCharacterSize(18);
		MenuOptiontext[i].setFillColor(sf::Color::White);
	}
	MenuOptiontext[wybranaopcja].setFillColor(sf::Color::Red);
	tekst1.setPosition(750.0f, 400);
	tekst2.setPosition(730.0f, 450);
	MenuOptiontext[0].setPosition(700.0f, 500);
	MenuOptiontext[1].setPosition(950.0f, 500);




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
	wybranaopcja = direction;
	MenuOptiontext[wybranaopcja].setFillColor(sf::Color::Red);

}



void Game::Saves()
{
}


///PODAWANIE NAZWY GRACZA
void Game::PodawanieImienie()
{

	NazwaPlayer.setFont(font);
	NazwaPlayer.setCharacterSize(24);
	NazwaPlayer.setPosition(300.f, 300.f);
	NazwaPlayer.setFillColor(sf::Color::White);

	int wprowadzaneimie = 0;

	while (!wprowadzaneimie)
	{
		sf::Event ww;
		while (MenuWindow->pollEvent(ww))
		{
			if (ww.type == sf::Event::TextEntered)
			{
				if (ww.text.unicode < 128)
				{
					imie += static_cast<char>(ww.text.unicode);
					NazwaPlayer.setString("Player name : " + imie);
					rysowanieImienia();
				}
			}
			else if (ww.type == sf::Event::KeyPressed)
			{
				if (ww.key.code == sf::Keyboard::Enter)
				{
					wprowadzaneimie++;
					MenuWindow->close();
					StartGame();

				}
			}
		}
	}


}

void Game::rysowanieImienia()
{
	RenderMenuTexture->clear(sf::Color::Black);
	MenuWindow->draw(Menusprite);
	while (MenuWindow->isOpen())
	{
		RenderMenuTexture->clear(sf::Color::Black);
		MenuWindow->draw(Menusprite);
		MenuWindow->draw(NazwaPlayer);
		MenuWindow->display();
	}
}


///TWORZENIE OKNA GRY I FUNKCJA ODPALANIA GRYI PRZEGRANIA I WYGRANIA
void Game::initGameWindow()
{
	this->GameWindow = new sf::RenderWindow(sf::VideoMode(950, 1000), "", sf::Style::Close | sf::Style::Titlebar);
	this->RenderGameTexture = (new sf::RenderTexture());
	
	
		if (!RenderGameTexture->create(static_cast<unsigned int>(GameWindow->getSize().x), static_cast<unsigned int>(GameWindow->getSize().y)))
		{
			std::cerr << "FAILED" << std::endl;
		}

		if (poziom_trudnosci == 1)
		{
			if (!GameTexture.loadFromFile("kosmos1.jpg"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			spriteGame.setTexture(GameTexture, true);
				spriteGame.scale(1.f, 1.f);
		}

		if (poziom_trudnosci == 2)
		{
			if (!GameTexture.loadFromFile("kosmos2.png"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			spriteGame.setTexture(GameTexture, true);
			spriteGame.scale(1.f, 1.f);
		}

		if (czyresetowany == false) {
			


			if (!GameMenuTexture.loadFromFile("sterowanie.png"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			GameMenuSprite.setTexture(GameMenuTexture);
			GameMenuSprite.setPosition(300, 300);
			GameMenuSprite.scale(2, 2);


			if (!znaczekT.loadFromFile("znaczekspace.png"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			znaczekS.setTexture(znaczekT, true);
			znaczekS.setPosition(310, -10);
			znaczekS.scale(0.75, 0.75);

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

			if (!GameOverT.loadFromFile("GameOver.png"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			GameOverS.setTexture(GameOverT, true);
			GameOverS.setPosition(270, 90);
			GameOverS.scale(0.75, 0.75);

			if (!winT.loadFromFile("Win.png"))
			{
				std::cerr << "FAILED LOADING" << std::endl;
			}
			winS.setTexture(winT, true);
			winS.setPosition(200, 200);
			winS.scale(1.3, 1.3);
		}
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
			{
				wstrzymana = true;
				stop();
			}
				
		}
}

void Game::StartGame()
{
	this->MenuWindow->close();

	
	
		initGameWindow();
		czyresetowany = true;

	

	if (poziom_trudnosci == 1)
	{
		Health = 4;
	}
	if (poziom_trudnosci == 2)
	{
		Health = 2;
	}

	font.loadFromFile("Emulogic-zrEw.ttf");
	
	GameWindow->setFramerateLimit(30);

	while (GameWindow->isOpen())
	{
		
		if (player.getRecoil() > 0)
		{
			player.odejmujrecoil();
		}
		update();

		render();
		if (Health == 0)
			GameOver();
		else if (Health > 0 && ileSpawnedEnemy == 0 && enemy.getEnemy().size() == 0)
			WinGame();

		GameWindow->display();
		
		this->GamePollEvents();
	}
	
}

///MENU W TRAKCIE GRY

void Game::stop()
{
	this->GameMenu = new sf::RenderWindow(sf::VideoMode(600, 600), "", sf::Style::Close | sf::Style::Titlebar);
	howPlay.setString(" HOW TO PLAY ");
	Gamemenu[0].setString("BACK TO GAME");
	Gamemenu[1].setString("BACK TO MENU");
	howPlay.setCharacterSize(25);
	howPlay.setFillColor(sf::Color::Yellow);
	howPlay.setFont(font);
	howPlay.setPosition(130, 30);
	for (int i = 0; i < 2; i++)
	{
		Gamemenu[i].setCharacterSize(17);
		Gamemenu[i].setFillColor(sf::Color::Yellow);
		Gamemenu[i].setFont(font);
		Gamemenu[i].setPosition(50 + 300 * i, 500);
	}
	GameMenuSprite.setPosition(100, 170);

	while (GameMenu->isOpen())
	{
		sf::Event event;
		while (GameMenu->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				GameMenu->close();
				wstrzymana = false;
				break;

			case sf::Event::KeyPressed:
				stop1(event.key);
				break;

			default:
				break;
			}
		}


		GameMenu->clear(sf::Color::Black);
		GameMenu->draw(howPlay);
		GameMenu->draw(GameMenuSprite);
		render();
		GameMenu->draw(Gamemenu[0]);
		GameMenu->draw(Gamemenu[1]);

		GameMenu->display();
	}
}

void Game::stop1(const sf::Event::KeyEvent& keyEvent)
{
	switch (keyEvent.code)
	{
	case sf::Keyboard::Left:
		stop2(0);
		break;

	case sf::Keyboard::Right:
		stop2(1);
		break;

	case sf::Keyboard::Enter:
		stop3();
		break;
	default:
		break;

	}

}

void Game::stop2(int direction)
{
	Gamemenu[wybranastop].setFillColor(sf::Color::White);
	wybranastop = direction;
	Gamemenu[wybranastop].setFillColor(sf::Color::Red);
}

void Game::stop3()
{
	switch (wybranastop)
	{
	case 0:
		this->GameMenu->close();
		wstrzymana = false;
		break;
	case 1:
		this->GameMenu->close();
		this->GameWindow->close();
		wstrzymana = false;
		resetowanieUstawien();
		initMenuWindow();
		mainMenuShowing();
		break;
	default:
		break;

	}
}

///PRZEGRANA I WYGRANA
void Game::GameOver()
{
	
	
	this->OVER[0].setString(" BACK TO MENU ");
	this->OVER[1].setString(" TRY AGAIN ");
	

	for (int i = 0; i < 2; ++i) {
		this->OVER[i].setFont(font);
		this->OVER[i].setCharacterSize(18);
		this->OVER[i].setPosition( 220.0f + i * 300.0f,400.f);
		this->OVER[i].setFillColor(sf::Color::White);
	}
	while (GameWindow->isOpen())
	{

		sf::Event event;
		while (GameWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				GameWindow->close();
				break;

			case sf::Event::KeyPressed:
				over1(event.key);
				break;

			default:
				break;
			}
		}


		RenderGameTexture->clear(sf::Color::Black);

		GameWindow->draw(spriteGame);

		
		render();
		
		GameWindow->draw(GameOverS);
		for (int i = 0; i < 2; ++i)
		{
			GameWindow->draw(OVER[i]);

		}

		GameWindow->display();
	}
}

void Game::over1(const sf::Event::KeyEvent& keyEvent)
{
	switch (keyEvent.code)
	{
	case sf::Keyboard::Left:
		over2(0);
		break;

	case sf::Keyboard::Right:
		over2(1);
		break;

	case sf::Keyboard::Enter:
		over3();
		break;
	default:
		break;

	}
}

void Game::over2(int direction)
{
	OVER[wybranaover].setFillColor(sf::Color::White);
	wybranaover = direction;
	OVER[wybranaover].setFillColor(sf::Color::Red);

}

void Game::over3()
{
	switch (wybranaover)
	{
	case 0:
		this->GameWindow->close();
		resetowanieUstawien();
		player.setPlayerPosition();
		this->initMenuWindow();
		mainMenuShowing();
		
		break;
	case 1:
		this->GameWindow->close();
		player.setPlayerPosition();
		resetowanieUstawien();
		StartGame();
		
		break;
	default:
		break;

	}
}

void Game::WinGame()
{
	this->OVER[0].setString(" BACK TO MENU ");
	this->OVER[1].setString(" TRY AGAIN ");


	for (int i = 0; i < 2; ++i) {
		this->OVER[i].setFont(font);
		this->OVER[i].setCharacterSize(18);
		this->OVER[i].setPosition(220.0f + i * 300.0f, 400.f);
		this->OVER[i].setFillColor(sf::Color::White);
	}
	while (GameWindow->isOpen())
	{

		sf::Event event;
		while (GameWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				GameWindow->close();
				break;

			case sf::Event::KeyPressed:
				over1(event.key);
				break;

			default:
				break;
			}
		}


		RenderGameTexture->clear(sf::Color::Black);

		GameWindow->draw(spriteGame);


		render();

		GameWindow->draw(winS);
		for (int i = 0; i < 2; ++i)
		{
			GameWindow->draw(OVER[i]);

		}

		GameWindow->display();
	}
}





Game::~Game()
{
	delete this->MenuWindow;
	delete this->RenderMenuTexture;
	delete this->GameWindow;
	delete this->RenderGameTexture;
}