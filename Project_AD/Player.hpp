#pragma once

#ifndef LEVELPARSER
#define LEVELPARSER


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
	virtual void update(float time) = 0;
};
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, right_Top, left_Top } state;
	int playerScore;
	bool isShoot;

	Player(sf::Image& image, sf::String Name, TileMap* lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; obj = lev->getAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		if (name == "player") {
		//	sprite.setTextureRect(sf::IntRect(0, 40, w, h));
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
		if ((sf:: Keyboard::isKeyPressed(sf::Keyboard::Right)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
			state = right_Top;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
			state = left_Top;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			isShoot = true;
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
		case right_Top:dx = speed; break;
		case left_Top:dx = -speed; break;
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


class Bullet :public Entity {
public:
	int direction;

	Bullet(sf::Image& image, sf::String Name, TileMap* lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl->getObjectsByName("solid");
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
		
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;
		case 1: dx = speed; dy = 0;   break;
		case 2: dx = 0; dy = -speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		case 4: dx = 0; dy = -speed;   break;
		case 5: dx = 0; dy = -speed;   break;
		case 6: dx = speed;  dy = -speed;   break;
		case 7: dx = -speed; dy = -speed; break;

		}

		x += dx * time;
		y += dy * time;

		if (x <= 0) { x = 1; life = false; }
		if (y <= 0) { y = 1; life = false; }

		for (int i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect)) 
			{
				life = false;
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);
	}
};



#endif // !LEVELPARSER