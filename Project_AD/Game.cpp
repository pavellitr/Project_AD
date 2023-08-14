#include "Game.hpp"

Game::Game() {
    m_Window.create(sf::VideoMode(1920, 1080), "Snake Game");

    constructMenu();

}

void Game::Start() {
    while (m_Window.isOpen())
    {
        menu();
        
        drawMenu();


    }
}

void Game::startEngine() {
	Engine = new Engine_mod::Engine(&m_Window);

	Engine->start();


}

void Game::input() {


}

void Game::update() {



}

void Game::draw() {



}

void Game::constructMenu() {

    if (!font.loadFromFile("Resourses\\fonts\\big-shot.ttf"))
        std::cout << "Font not found!\n";

    start = new Button("Start", { 994, 179 }, 30, sf::Color::Black, sf::Color::White);
    escape = new Button("Escape", { 994, 179 }, 30, sf::Color::Black, sf::Color::White);

    start->setFont(font);
    escape->setFont(font);

    start->setPosition({ 463, 570 });
    escape->setPosition({ 463, 795 });

    this->Background = new sf::Texture;
    this->Background->loadFromFile("Resourses\\images\\Background.png");

    this->BackgroundSprite = new sf::Sprite();
    this->BackgroundSprite->setTexture(*Background);
}

void Game::menu() {
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_Window.close();
        case sf::Event::MouseMoved:
            if (start->isMouseOver(m_Window)) {
                start->setBackColor(sf::Color::Magenta);
            }
            else {
                start->setBackColor(sf::Color::Black);
            }
            if (escape->isMouseOver(m_Window)) {
                escape->setBackColor(sf::Color::Magenta);
            }
            else {
                escape->setBackColor(sf::Color::Black);
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (start->isMouseOver(m_Window)) {
                std::cout << "Hello " << "\n";
            }
            else if (escape->isMouseOver(m_Window)) {
                m_Window.close();
            }

        }
    }
}

void Game::drawMenu() {
    m_Window.clear();
    m_Window.draw(*BackgroundSprite);
    start->drawTo(m_Window);
    escape->drawTo(m_Window);
    m_Window.display();
}