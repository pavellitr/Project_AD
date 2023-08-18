#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Button.hpp"
#include "Engine.hpp"

class Game
{
public:
	Game();
	void Start();

private:

	sf::RenderWindow m_Window;
	Engine* engine;

	void startEngine();

	////////////////////////////  MENU
	sf::Texture* Background;
	sf::Sprite* BackgroundSprite;
	sf::Font font;

	Button* start;
	Button* escape;
	Button* saves;

	void constructMenu();
	void menu();
	void drawMenu();
	////////////////////////////  MENU





};