#pragma once

#ifndef ANIMAL_H
#define ANIMAL_H

#include "Obstacle.h"

class CAnimal : public CObstacle {
public:
	CAnimal(POINT pos, int dir, int speed) : CObstacle(pos, dir, speed) {
		m_key = {
			" /\\-/\\ ",
			"(=^Y^=)",
			" (>o<) "
		};
	}
private:
	void talk() { cout << "\b"; }
	void draw(string s, POINT p, bool dark) {
		drawTurn.lock();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		CObstacle::draw(s, p, dark);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		drawTurn.unlock();
	}

	void save(FILE* f) {
		//fprintf(f, "%c ", 'A');
		char type = 'A';
		fwrite(&type, sizeof(type), 1, f);
		CObstacle::save(f);
	}
};

#endif