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
	void talk() { cout << "Gau gau!"; }

	void draw(string s) {
		drawTurn.lock();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		CObstacle::draw(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		drawTurn.unlock();
	}

	void save(char* dir) {
		FILE *f = fopen(dir, "a");
		fprintf(f, "%c ", 'V');
		fclose(f);
		CObstacle::save(dir);
	}
};

#endif