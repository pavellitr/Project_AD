#include "Engine.hpp"



Engine::Engine(sf::RenderWindow* window) {
	m_Window = window;

	Background = new sf::Texture;
	Background->loadFromFile("Resourses\\images\\Background.png");

	BackgroundSprite = new sf::Sprite;
	BackgroundSprite->setTexture(*Background);

	levels = new LevelBuffer;
	
	constructPause();

	
	
	heroImage.loadFromFile("Resourses\\images\\Head.png");
	bulletImage.loadFromFile("Resourses\\images\\bullet.png");

	Object player = levels->BringLevel(1)->getObject("player");

	p = new Player (heroImage, "Player1", levels->BringLevel(1), player.GetX(), player.GetY(), 40, 40, 100, 100, 5, 10, 25);
	

}

void Engine::start() {

	sf::Clock clockinput;
	sf::Clock Clock;
	sf::Clock CDTimer;
	while (m_Window->isOpen()) {
		float time = Clock.getElapsedTime().asMicroseconds();
		float CD = CDTimer.getElapsedTime().asMilliseconds();
		Clock.restart();
		input(&clockinput);

		time = time / 800;
		
		if (paused == false) {
			//игру писать здесь

			if (p->getIsShoot() == true && CD > 500) {
				p->setIsShoot(false); entities.push_back(new Bullet(bulletImage, "Bullet","bullet", levels->BringLevel(1), p->getX(), p->getY(), 16, 16, p->getState()));
				CDTimer.restart();

			}
			for (it = entities.begin(); it != entities.end();)
			{
				Entity* b = *it;
				b->update(time);
				if (b->life == false) { it = entities.erase(it); delete b; }
				else it++;
			}		
			p->update(time);
			
		}


		if (escaped == true) {
			break;
		}
		
		draw();
	}
}


void Engine::update() {
	p->update(time);

}
void Engine::draw() {
	m_Window->clear(sf::Color::Black);
	m_Window->draw(*BackgroundSprite);
	
	for (it = entities.begin(); it != entities.end(); it++) {
		m_Window->draw((*it)->sprite);

	}

	m_Window->draw(*levels->BringLevel(1));
	m_Window->draw(p->getSprite());

	if (paused == true) {
		drawPause();
	}
	

	m_Window->display();

}

void Engine::input(sf::Clock* clock) {
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_Window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) and clock->getElapsedTime().asMilliseconds() > 100) {
			if (paused == false) {
				paused = true;
				clock->restart();
			}
			else {
				clock->restart();
				paused = false;
			}
		}
		if (paused == true) {
			switch (event.type)
			{
			case sf::Event::Closed:
				m_Window->close();
			case sf::Event::MouseMoved:
				if (resume->isMouseOver(*m_Window)) {
					resume->setBackColor(sf::Color::Color(26, 26, 26));
				}
				else {
					resume->setBackColor(sf::Color::Black);
				}
				if (escape->isMouseOver(*m_Window)) {
					escape->setBackColor(sf::Color::Color(26, 26, 26));
				}
				else {
					escape->setBackColor(sf::Color::Black);
				}
				if (save->isMouseOver(*m_Window)) {
					save->setBackColor(sf::Color::Color(26, 26, 26));
				}
				else {
					save->setBackColor(sf::Color::Black);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (resume->isMouseOver(*m_Window)) {
					paused = false;
				}
				else if (escape->isMouseOver(*m_Window)) {
					std::cout << "Hello World!" << std::endl;
					escaped = true;

				}
				else if (save->isMouseOver(*m_Window)) {
					std::cout << "Hello World!" << std::endl;
				}

			}
		}
	}




}

void Engine::constructPause() {
	if (!font.loadFromFile("Resourses\\fonts\\big-shot.ttf"))
		std::cout << "Font not found!\n";

	BackgroundMenu = new sf::Texture;
	BackgroundMenu->loadFromFile("Resourses\\images\\BackgroundMenu.png");
	
	BackgroundMenuSprite = new sf::Sprite;
	BackgroundMenuSprite->setTexture(*BackgroundMenu);
	BackgroundMenuSprite->setTextureRect(sf::IntRect(10, 10, 700, 500));
	BackgroundMenuSprite->setPosition({610, 290});

	resume = new Button("Resume", { 662, 120 }, 20, sf::Color::Black, sf::Color::White);
	save = new Button("Save game", { 662, 120 }, 20, sf::Color::Black, sf::Color::White);
	escape = new Button("Escape", { 662, 120 }, 20, sf::Color::Black, sf::Color::White);

	resume->setFont(font);
	save->setFont(font);
	escape->setFont(font);

	resume->setPosition({ 629, 305 });
	save->setPosition({ 629, 480 });
	escape->setPosition({ 629, 655 });


	paused = false;
	escaped = false;

}

void Engine::drawPause() {
	m_Window->draw(*BackgroundMenuSprite);
	resume->drawTo(*m_Window);
	escape->drawTo(*m_Window);
	save->drawTo(*m_Window);
}
