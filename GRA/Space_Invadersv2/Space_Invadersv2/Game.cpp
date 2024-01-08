#include "Game.h"


Game::Game()
{

}

void Game::run()
{
	this->mainMenuShowing();
}

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

void Game::update()
{
	if (endgame == false)
	{
		player.PoruszaniePlayer();
		for (auto& e : player.ShotedBullet)
		{
			e.poruszanieBullet(enemy.GetPoints(), enemy.getEnemy());
		}
		enemy.PoruszanieEnemy(poziom_trudnosci, Points, Health, player.GetPlayer());

		Points = enemy.GetPoints() + player.GetPP();
		Health = enemy.GetHealth();

		if (Health == 0 || enemy.Czywygrana() ==0 )
		{
			endgame = true;
			if (Health == 0)
				GameOver();
			if (enemy.Czywygrana() == 0)
				WinGame();
		}

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
	this ->Point.setString(PointString);
	this->Point.setPosition(860, 35);
	this->Point.setFont(font);
	this->Point.setCharacterSize(60);
	this->Point.setCharacterSize(27);
	this->Point.setFillColor(sf::Color::Yellow);
	this->GameWindow->draw(this->Point);
}


///

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

	if (poziom_trudnosci == 1)
	{
		Health = 4;
	}
	if (poziom_trudnosci == 2)
	{
		Health = 2;
	}

	font.loadFromFile("Arial.ttf");
	this->MenuWindow->close();
	initGameWindow();
	

	while (GameWindow->isOpen())
	{
		
		if (player.getRecoil() > 0)
		{
			player.odejmujrecoil();
		}
		update();

		render();

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
					wprowadzaneimie ++;
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


void Game::GameOver()
{
}

void Game::WinGame()
{
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


Game::~Game()
{
	delete this->MenuWindow;
	delete this->RenderMenuTexture;
	delete this->GameWindow;
	delete this->RenderGameTexture;
}