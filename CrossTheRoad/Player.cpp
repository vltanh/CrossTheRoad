#include "Player.h"

void CPlayer::update() {
	Sleep(75);

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
	int t = 8;
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

	PlaySound("explode.wav", NULL, SND_ASYNC);

	SetColor(LIGHTRED);
	GotoXY(m_pos.x, m_pos.y);
	cout << " ";

	Sleep(800);
	srand(time(NULL));
	int r = 4;
	for (int i = 0; i < 30; i++) {
		int dx = m_pos.x + rand() % (2*r + 1) - r;
		int dy = m_pos.y + rand() % (2*r + 1) - r;
		while (dx >= WIDTH_CONSOLE || dx < 1 || dy >= HEIGHT_CONSOLE || dy < 1 && dx*dx + dy*dy > r*r) {
			dx = m_pos.x + rand() % (2*r + 1) - r;
			dy = m_pos.y + rand() % (2*r + 1) - r;
		}

		int clr = rand() % 2;
		if (clr == 0) SetColor(LIGHTRED);
		else SetColor(WHITE);

		GotoXY(dx, dy);
		cout << ".";
	}

	SetColor(WHITE);
}

void CPlayer::save(FILE* f) {
	//fprintf(f, "%d %d\n", m_pos.x, m_pos.y);
	fwrite(&m_pos, sizeof(m_pos), 1, f);
}

void CPlayer::load(FILE* f) {
	//fscanf(f, "%d %d\n", &m_pos.x, &m_pos.y);
	fread(&m_pos, sizeof(m_pos), 1, f);
}