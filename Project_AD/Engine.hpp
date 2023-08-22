#pragma once
//#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Level_buffer.hpp"
#include <iostream>
#include <list>


class Engine
{
public:
	Engine(sf::RenderWindow* window);
	void start();

private:
	sf::RenderWindow* m_Window;

	sf::Texture* Background;
	sf::Sprite* BackgroundSprite;

	sf::Image heroImage;

	sf::Image BulletImage;
	Bullet* bul;
	

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;

	LevelBuffer* levels;
		 
	
	Player* p;
	float time;

	void input(sf::Clock* clock);
	void update();
	void draw();

	///////////////////////////////PAUSE
	sf::Texture* BackgroundMenu;
	sf::Sprite* BackgroundMenuSprite;
	sf::Font font;

	Button* resume;
	Button* escape;
	Button* save;

	void constructPause();
	void drawPause();
	bool paused;
	bool escaped;
	//////////////////////////////PAUSE



};