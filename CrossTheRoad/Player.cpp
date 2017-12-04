#include "Player.h"

void CPlayer::update() {
	this_thread::sleep_for(75ms);

	if (STATE == 0) return;

	draw(" ");

	if (isPressed(KEY_D))
		moveRight();
	else if (isPressed(KEY_W))
		moveUp();
	else if (isPressed(KEY_S))
		moveDown();
	else if (isPressed(KEY_A))
		moveLeft();

	draw("X");
}

void CPlayer::moveRight() {
	if (m_pos.x < WIDTH_BOARD) m_pos.x++;
}

void CPlayer::moveLeft() {
	if (m_pos.x > 1) m_pos.x--;
}

void CPlayer::moveDown() {
	if (m_pos.y < HEIGHT_BOARD) m_pos.y++;
}

void CPlayer::moveUp() {
	if (m_pos.y > 1) m_pos.y--;
}

void CPlayer::draw(string s, int st) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	drawTurn.lock();

	SetConsoleTextAttribute(hConsole, (st == 0) ? 9 : 7);
	GotoXY(m_pos.x, m_pos.y);
	cout << s;
	SetConsoleTextAttribute(hConsole, 15);

	drawTurn.unlock();
}

void CPlayer::kill() {
	int t = 10;
	while (t--) {
		SetColor(LIGHTRED);
		GotoXY(m_pos.x, m_pos.y);
		cout << "X";

		Sleep(300 / (10 - t));

		SetColor(WHITE);
		GotoXY(m_pos.x, m_pos.y);
		cout << "X";

		Sleep(300 / (10 - t));
	}

	SetColor(LIGHTRED);
	GotoXY(m_pos.x, m_pos.y);
	cout << "X";

	SetColor(WHITE);
}

void CPlayer::save(char* dir) {
	FILE* f = fopen(dir, "a");
	fprintf(f, "%d %d\n", m_pos.x, m_pos.y);
	fclose(f);
}

void CPlayer::load(FILE* f) {
	fscanf(f, "%d %d\n", &m_pos.x, &m_pos.y);
}