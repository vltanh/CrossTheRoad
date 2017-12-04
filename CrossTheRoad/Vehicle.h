#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include "Obstacle.h"

class CVehicle : public CObstacle {
public:
	CVehicle(POINT pos, int dir, int speed) : CObstacle(pos, dir, speed) {
		m_key = {
			"   __    ",
			" _/ L\\__",
			"'-o---o-'"
		};
	}
private:
	void talk() { PlaySound("vehicle041.wav", NULL, SND_FILENAME); }

	void draw(string s, POINT p, bool dark) {
		drawTurn.lock();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		CObstacle::draw(s, p, dark);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		drawTurn.unlock();
	}

	void save(FILE* f) {
		//fprintf(f, "%c ", 'V');
		char type = 'V';
		fwrite(&type, sizeof(type), 1, f);
		CObstacle::save(f);
	}
};

#endif