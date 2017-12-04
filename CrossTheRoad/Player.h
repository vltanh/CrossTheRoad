#pragma once

#include "Utils.h"
#include "GameWindow.h"

class CPlayer : public GameWindow {
private:
	POINT m_pos;
	int m_state;
public:
	CPlayer() {}
	CPlayer(int w, int h) { m_pos = { w, h }; m_state = 1; }
	CPlayer& operator = (const CPlayer& p) { m_pos = p.m_pos; m_state = p.m_state; return(*this); }

	bool isDead() { return m_state == 0; }
	bool isDone() { return m_pos.y == 1; }

	void update();
	void draw(string, int = 1);
	void kill();
	void save(FILE*);
	void load(FILE*);

	POINT getPos() { return m_pos; }

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
};