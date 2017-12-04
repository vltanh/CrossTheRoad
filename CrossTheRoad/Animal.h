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
	void draw(string s) {
		drawTurn.lock();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		CObstacle::draw(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		drawTurn.unlock();
	}

	void save(char* dir) {
		FILE *f = fopen(dir, "a");
		fprintf(f, "%c ", 'A');
		fclose(f);
		CObstacle::save(dir);
	}
};

#endif