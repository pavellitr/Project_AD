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
	//���� ���� ����� �������{
		//Level* level = new Level();
		//LevelBuf.pushback(level)



}

Level* LevelBuffer::BringLevel(int num){ //����� ��������� ���������� �������
	return LevelBuf[num - 1];
	}
