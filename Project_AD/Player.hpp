#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "levelParser.hpp"



class Entity {
public:
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	Entity(sf::Image& image, sf::String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	sf::FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return sf::FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}
};
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay } state;
	int playerScore;

	Player(sf::Image& image, sf::String Name, TileMap* lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; obj = lev->getAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		if (name == "Player1") {
			//sprite.setTextureRect(IntRect(220, 444, w, h));
		}
	}

	void control() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			state = left;
			speed = 0.3;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			state = right; speed = 0.3;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (onGround)) {
			state = jump; dy = -0.7; onGround = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			state = down;

		}
	}



	void checkCollisionWithMap(float Dx, float Dy)
	{

		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
	}

	void update(float time)
	{
		control();
		switch (state)
		{
		case right:dx = speed; break;
		case left:dx = -speed; break;
		case up: break;
		case down: dx = 0; break;
		case stay: break;
		}
		x += dx;
		checkCollisionWithMap(dx, 0);
		y += dy;

		checkCollisionWithMap(0, dy);
		sprite.setPosition(sf::Vector2f(x + w / 2, y + h / 2));
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }


		dy = dy + 0.0015 * time;
	}
};

