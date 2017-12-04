#include "Utils.h"

void fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();

	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME & ~WS_HSCROLL & ~WS_VSCROLL;
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	RECT r;
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, r.left, r.top, 1000, 600, TRUE);
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &info);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool isPressed(int key) {
	//return GetAsyncKeyState(key);
	return GetKeyState(key) & 0x8000;
}

void pressEnter()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwFlags = KEYEVENTF_UNICODE;
	ip.ki.wScan = VK_RETURN; //VK_RETURN is the code of Return key
	ip.ki.wVk = 0;

	ip.ki.dwExtraInfo = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

void ClearConsoleInputBuffer()
{
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}

void clearRow(int startX, int startY, int endY, int len) {
	if (endY == -1)
		endY = startY;
	for (int i = startY; i <= endY; i++) {
		GotoXY(startX + 1, i);
		int n = len;
		while (n--) cout << ' ';
	}
}

void SetColor(int clr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}