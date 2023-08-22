#pragma once

#include <vector>
#include "LevelParser.hpp"

class LevelBuffer
{
public:
	inline LevelBuffer();
	inline TileMap* BringLevel(int num);



private:
	std::vector <TileMap*> LevelBuf;

};

LevelBuffer::LevelBuffer()
{
	//пока есть файлы уровней{
		TileMap* level = new TileMap;
		level->load("map2.tmx");
		LevelBuf.push_back(level);



}

TileMap* LevelBuffer::BringLevel(int num){ //чтобы запускать конкретный уровень


	return LevelBuf[num - 1];
	}
