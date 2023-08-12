#include "Engine.hpp"



Engine_mod::Engine::Engine() {
	//Вставишь сюда ссылку 
	m_Window->create(sf::VideoMode(600, 600), "KekWait");

}

void Engine_mod::Engine::start() {

	sf::Clock clockUpdate;
	while (m_Window->isOpen()) {

		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_Window->close();
		}

		input();

		sf::Int32 dU = clockUpdate.getElapsedTime().asMilliseconds();

		if (dU >= 100) {
			update();
			clockUpdate.restart();
		}

		draw();



	}
}


void Engine_mod::Engine::update() {
	

}
void Engine_mod::Engine::draw() {
	m_Window->clear(sf::Color::Black);
//	m_Window->draw();
	m_Window->display();

}

void Engine_mod::Engine::input() {



}
