#pragma once

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "Utils.h"

class GameWindow {
protected:
	int WIDTH_BOARD;
	int HEIGHT_BOARD;
	int WIDTH_CONSOLE;
	int HEIGHT_CONSOLE;
	int LANE_HEIGHT;
	int NOBSTACLES;
public:
	GameWindow();

	int getWidthBoard() { return WIDTH_BOARD; }
	int getHeightBoard() { return HEIGHT_BOARD; }
	int getWidthConsole() { return WIDTH_CONSOLE; }
	int getHeightConsole() { return HEIGHT_CONSOLE; }
	int getNumberOfLanes() { return NOBSTACLES; }

	void setWidthBoard(int w) { WIDTH_BOARD = w; }
	void setHeightBoard(int h) { HEIGHT_BOARD = h; }
	void setWidthConsole(int w) { WIDTH_CONSOLE = w; }
	void setHeightConsole(int h) { HEIGHT_CONSOLE = h; }
	void setNumberOfLanes(int n) { NOBSTACLES = n; }
};

#endif