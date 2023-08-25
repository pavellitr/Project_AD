#pragma once

#ifndef LEVELPARSER
#define LEVELPARSER


#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "levelParser.hpp"


class Entity
{
public:
	Entity(sf::Image& image, sf::String Name, sf::String Type, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; type = Type; moveTimer = 0;
		speed = 0; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	};


	std::vector <Object> objects;
	float dx, dy, x, y, speed, moveTimer;
	int w, h;
	bool life, isMove, onGround;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name, type;
	
	sf::FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return sf::FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

	virtual void control() = 0;
};

class Player : private Entity
{
public:
	Player(sf::Image& image, sf::String Name, sf::String Type, TileMap* lev, float x, float y, int w, int h, int mp, int hp, int str, int dex, int integ) : Entity(image, Name, Type, x, y, w, h) {
		this->hp = hp; this->mp = mp; this->integer = integ; this->dex = dex; this->maxmp = 17 * integer - 3 * this->str; this->maxhp = 35 * this->str + 6 * this->dex;
		objects = lev->getAllObjects();
	}

	int getInt() {
		return integer;
	}

	int getDex() {
		return dex;
	}

	int getStr() {
		return str;
	}

	int getHP() {
		return hp;
	}

	int getMP() {
		return mp;
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
		if (hp <= 0) { life = false; }
		if (!isMove) { speed = 0; }


		dy = dy + 0.0015 * time;
	}

	sf::Sprite getSprite() {
		return sprite;
	}


private:
	enum { left, right, up, down, jump, stay } state;
	int hp, maxhp, maxmp, mp, str, dex, integer;

	void control() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			state = left;
			speed = 0.3;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			state = right; speed = 0.3;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
			state = up;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			state = down;

		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (onGround)) {
			state = jump; dy = -0.7; onGround = false;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{

		for (int i = 0; i < objects.size(); i++)//проходимся по объектам
			if (getRect().intersects(objects[i].rect))//проверяем пересечение игрока с объектом
			{
				if (objects[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) { y = objects[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = objects[i].rect.top + objects[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = objects[i].rect.left - w; }
					if (Dx < 0) { x = objects[i].rect.left + objects[i].rect.width; }
				}
			}
	}


};




class NPC : private Entity
{
public:
	NPC(sf::Image& image, sf::String Name, sf::String Type, TileMap* lev, float x, float y, int w, int h, int mp, int hp, int str, int dex, int integ) : Entity(image, Name, Type, x, y, w, h) {

	}


private:

};















#endif // !LEVELPARSER