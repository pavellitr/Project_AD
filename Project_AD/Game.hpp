#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Button.hpp"

class Game
{
public:
	Game();
	void Start();

private:

	sf::RenderWindow* m_Window;
	//Engine_mod::Engine* Engine;

	void startEngine();

	sf::Texture* Background;
	
	//Button Start;
	//Button Escape;

	void input();
	void update();
	void draw();



};