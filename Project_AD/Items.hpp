#pragma once 
#include "levelParser.hpp"
#include <vector>
#include <iostream>

class Item {

public:
	Item(Object obj, int ID, TileMap* lvl) {
		w = obj.GetWidth(); h = obj.GetHeight(); x = obj.GetX(); y = obj.GetY();
		ItemObject = &obj;


		ItemID = ID;
		if (ItemID == 1) texture.loadFromFile("Resourses\\images\\Apple.png");
		sprite = new sf::Sprite;
		sprite->setTexture(texture);
		sprite->setOrigin(obj.GetWidth() / 2, obj.GetHeight() / 2);
		sprite->setPosition(obj.GetX()+w/2, obj.GetY()+h/2);
		

	}


	float w, h, x, y;
	

	std::vector <Object> itemsObjects;
	std::vector <Object> Objects;
	Object* ItemObject;

	int ItemID;

	int hp = 0, maxhp = 0, maxmp = 0, mp = 0, str = 0, dex = 0, integer = 0;

	bool PickUped = false;

	sf::Texture texture;
	sf::Sprite* sprite;
	

	Object* GetObjectOfItem() {
		return ItemObject;
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(x, y, w, h);
	}

	virtual	sf::Sprite* getSprite() {

		return sprite;
	}

	int  getID() {
		return ItemID;
	}
	virtual void update() = 0;
	

};

class ItemStatsUp : public Item {
public:
	ItemStatsUp(Object obj, int ID, TileMap* lvl) : Item(obj, ID, lvl) {
		this->ItemID = ID;
		
	// Objects = lvl->getAllObjects();

		switch (ItemID)
		{
		case 1: hp = 20; break;
		}

	}
	
	

	void update() {
		

	}
private:
	

	

};
class ItemActive : public Item {
public:
	ItemActive(Object obj, int ID, TileMap* lvl) : Item(obj, ID, lvl) {

	}

		void update() {


	}

};

class ItemPrimaryWeapon : public Item {



};