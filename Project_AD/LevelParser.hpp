﻿#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include "SFML/Graphics.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <cctype>

class Object
{
public:
	Object(float x, float y, float width, float height) : rect(x, y, width, height)
	{
		x_Place = x;
		y_Place = y;
		Width = width;
		Height = height;


	}

	 int          GetPropertyInt(const std::string& name);
	 float       GetPropertyFloat(const std::string& name);
	 std::string  GetPropertyString(const std::string& name);

	 float		GetX() { return x_Place; };
	 float		GetY() { return y_Place; };
	 float		GetWidth() { return Width; };
	 float		GetHeight() { return Height; };

	std::string name;
	std::string type;
	std::map<std::string, std::string> properties;
	sf::FloatRect rect;
	float x_Place;
	float y_Place;
	float Width;
	float Height;

};

class TileMap : public sf::Drawable
{
public:
   ~TileMap();

	bool load(const std::string& tmx_file_path);

	  Object               getObject(const std::string& name);
	  std::vector<Object>  getObjectsByName(const std::string& name);
	  std::vector<Object>  getObjectsByType(const std::string& type);
	  std::vector<Object>& getAllObjects();

private:
	 void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture* texture;
	std::vector<sf::VertexArray> tile_layers;
	std::vector<Object>          objects;
};
