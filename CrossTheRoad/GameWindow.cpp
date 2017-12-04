#include "GameWindow.h"

GameWindow::GameWindow() {
	WIDTH_BOARD = 50;
	HEIGHT_BOARD = 20;
	WIDTH_CONSOLE = WIDTH_BOARD + 2;
	HEIGHT_CONSOLE = HEIGHT_BOARD + 2;
	LANE_HEIGHT = 3;
	NOBSTACLES = (HEIGHT_BOARD - 2) / LANE_HEIGHT;

	STATE = 1;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	fixConsoleWindow();
	hideCursor();
}