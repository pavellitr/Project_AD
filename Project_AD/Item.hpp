#pragma once

#ifndef LEVELPARSER
#define LEVELPARSER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "LevelParser.hpp"
#include "Player.hpp"

class Item
{
public:
	Item (sf::Image& image, sf::String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; life = true; 
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);


	};

	
	float x, y;
	int w, h;
	bool life;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;

	sf::FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return sf::FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

	virtual void function() = 0;

};









#endif // !LEVELPARSER
