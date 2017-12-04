#include "GameWindow.h"

GameWindow::GameWindow() {
	LANE_HEIGHT = 3;
	NOBSTACLES = 4;
	WIDTH_BOARD = 100;
	HEIGHT_BOARD = NOBSTACLES*LANE_HEIGHT + 2;
	WIDTH_CONSOLE = WIDTH_BOARD + 2;
	HEIGHT_CONSOLE = HEIGHT_BOARD + 2;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); //cout.tie(NULL);

	fixConsoleWindow();
	hideCursor();
}