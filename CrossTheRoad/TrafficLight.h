#pragma once
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "Utils.h"
#include "GameWindow.h"

class CTrafficLight : public GameWindow {
private:
	int m_state;
public:
	CTrafficLight() { m_state = 1; }
	CTrafficLight& operator = (const CTrafficLight& tl) { m_state = tl.m_state; return(*this); }
	void draw() {
		drawTurn.lock();
		if (m_state == 0) {
			SetColor(LIGHTRED);
		}
		else if (m_state == 1) {
			SetColor(LIGHTGREEN);
		}
		GotoXY(0, 0);
		cout << "L";
		SetColor(WHITE);
		drawTurn.unlock();
	}

	void switchLight() {
		m_state = 1 - m_state;
	}

	int& isGreen() { return m_state; }
};

#endif