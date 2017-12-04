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
	atomic<int> STATE;
public:
	GameWindow();
};

#endif