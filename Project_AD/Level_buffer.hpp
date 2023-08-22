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
	//���� ���� ����� �������{
		TileMap* level = new TileMap;
		level->load("map2.tmx");
		LevelBuf.push_back(level);



}

TileMap* LevelBuffer::BringLevel(int num){ //����� ��������� ���������� �������


	return LevelBuf[num - 1];
	}
