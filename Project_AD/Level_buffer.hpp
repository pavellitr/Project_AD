#pragma once

#include <vector>
#include "Level.hpp"

class LevelBuffer
{
public:
	LevelBuffer();
	Level* BringLevel(int num);



private:
	std::vector <Level*> LevelBuf;

};

LevelBuffer::LevelBuffer()
{
	//пока есть файлы уровней{
		//Level* level = new Level();
		//LevelBuf.pushback(level)



}

Level* LevelBuffer::BringLevel(int num){ //чтобы запускать конкретный уровень
	return LevelBuf[num - 1];
	}
