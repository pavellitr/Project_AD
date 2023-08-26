#pragma once

#ifndef LEVELPARSER
#define LEVELPARSER


#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "levelParser.hpp"
#include "Items.hpp"


class Entity
{
public:
	Entity(sf::Image& image, sf::String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	};


	std::vector <Object> objects;
	std::list<Item*> Items;
	std::list<Item*>::iterator itItem;

	float dx, dy, x, y, speed, moveTimer;
	int w, h;
	bool life, isMove, onGround;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	
	sf::FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return sf::FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

	virtual void control() = 0;
	virtual void update(float time) = 0;
};

class Player : private Entity
{
public:
	Player(sf::Image& image, sf::String Name, std::list<Item*> items , TileMap* lev, float x, float y, int w, int h, int mp, int hp, int str, int dex, int integ) : Entity(image, Name, x, y, w, h) {
		this->hp = hp; this->mp = mp; this->integer = integ; this->dex = dex; this->maxmp = 17 * integer - 3 * this->str; this->maxhp = 35 * this->str + 6 * this->dex;
		objects = lev->getAllObjects();
		Items = items;
		std::list<Item*> Items;
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

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getState() {
		return state;
	}
	int getIsShoot() {
		return isShoot;
	}
	void setIsShoot(bool flag) {
		isShoot = flag;
	}
	int getPickUP() {
		return pickUP;
	}
	void setPickUP(bool flag) {
		pickUP= flag;
	}
	sf::Sprite getSprite() {
		return sprite;
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
		checkCollisionsWithItems();
		sprite.setPosition(sf::Vector2f(x + w / 2, y + h / 2));
		if (hp <= 0) { life = false; }
		if (!isMove) { speed = 0; }


		dy = dy + 0.0015 * time;
	}


	void PickUpItemStatsUP(int ID) {
		switch (ID)
		{
		case 1:hp += 20; break;
		}
		

	}

private:
	enum { left, right, up, down, jump, stay } state;
	int hp=100, maxhp=100, maxmp=200, mp=200, str=10, dex=10, integer=10;
	bool isShoot=false, pickUP=false;
	
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			isShoot = true;

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

	void checkCollisionsWithItems() {
		
	 for (itItem = Items.begin(); itItem != Items.end();itItem++)
		{
		 Item* b = *itItem;
			if (getRect().intersects(b->getRect())) {
				
				b->PickUped = true;
				
			}	
		}
	}


};




class NPC : private Entity
{
public:
	NPC(sf::Image& image, sf::String Name, TileMap* lev, float x, float y, int w, int h, int mp, int hp, int str, int dex, int integ) : Entity(image, Name,  x, y, w, h) {

	}


private:

};

class Bullet : public Entity {
public:
	int direction;

	Bullet(sf::Image& image, sf::String Name, TileMap * lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		objects = lvl->getObjectsByName("solid");
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;

	}

	void control() {

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
		if (x >= 1920) { x = 1; life = false; }
		if (y <= 0) { y = 1; life = false; }

		for (int i = 0; i < objects.size(); i++) {
			if (getRect().intersects(objects[i].rect))
			{

				life = false;

			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);
	}
};













#endif // !LEVELPARSER