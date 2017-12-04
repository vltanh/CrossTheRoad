#pragma once

#ifndef COBSTACLE_H
#define COBSTACLE_H

#include "Utils.h"
#include "GameWindow.h"

class CObstacle : public GameWindow {
protected:
	POINT m_pos;
	int m_dir;
	int m_speed;
	vector<string> m_key;
public:
	CObstacle(POINT pos, int dir, int speed) {
		m_pos = pos;
		m_dir = dir;
		m_speed = speed;
	}

	POINT getPos() { return m_pos; }

	virtual void draw(string, POINT, bool);
	void update(POINT, bool);
	virtual void talk() = 0;
	virtual void save(FILE*);

	bool isCollided(const POINT& p) {
		int x = p.x - m_pos.x;
		int y = p.y - m_pos.y;

		return (x >= 1 && x <= m_key[0].size() && y >= 0 && y <= m_key.size() - 1) && m_key[y][x - 1] != ' ';
	}
};

#endif