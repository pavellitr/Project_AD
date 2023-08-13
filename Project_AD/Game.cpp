#include "Game.hpp"

Game::Game() {
	m_Window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Project_AD", sf::Style::Fullscreen);

	//ñäåëàòü settexture  äëÿ áıêà
	//ñîçäàòü 2 êíîïêè
}

void Game::Start() {
    while (m_Window->isOpen())
    {
        sf::Event event;
        while (m_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_Window->close();
        }




    }
}

void Game::startEngine() {
	//Engine = new Engine_mod::Engine(m_Window);

	//Engine->start();


}