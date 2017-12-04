#include "Game.h"
#include "Animal.h"
#include "Vehicle.h"

mutex a;

CGame::CGame() : GameWindow() {
	p = CPlayer(WIDTH_BOARD / 2, HEIGHT_BOARD);
	m_level = 1;
	DARK_MODE = false;
}

CGame::~CGame()
{
	for (int i = 0; i < m_obs.size(); i++)
		delete m_obs[i];
}

void CGame::initGame() {
	system("cls");
	int h0 = 3;

	vector<string> a = {
		"   ______                        __  __            ____                  __",
		"  / ____/________  __________   / /_/ /_  ___     / __ \\____  ____ _____/ /",
		" / /   / ___/ __ \\/ ___/ ___/  / __/ __ \\/ _ \\   / /_/ / __ \\/ __ `/ __  / ",
		"/ /___/ /  / /_/ (__  |__  )  / /_/ / / /  __/  / _, _/ /_/ / /_/ / /_/ /  ",
		"\\____/_/   \\____/____/____/   \\__/_/ /_/\\___/  /_/ |_|\\____/\\__,_/\\__,_/   "
	};

	int w = a[0].size();
	int h = a.size();
	POINT start = { WIDTH_CONSOLE / 2 - w / 2, h0};
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			GotoXY(start.x + j, start.y + i);
			cout << a[i][j];
		}
	}

	int left = WIDTH_CONSOLE / 2 - strlen("[N]ew Game") / 2;
	GotoXY(left, h0 + h + 4);
	cout << "[N]ew Game";
	GotoXY(left, h0 + h + 5);
	cout << "[L]oad Game";
	GotoXY(left, h0 + h + 6);
	cout << "[S]ettings";
	GotoXY(left, h0 + h + 7);
	cout << "[E]xit";

	char temp = 0;
	while (temp != 'L' && temp != 'S' && temp != 'N' && temp != 'E') {
		temp = toupper(_getch());
		if (temp == 'N') {
			drawLoading(h0 + 3);
			resetGame();
			startGame();
		}
		else if (temp == 'L') {
			loadGame(true);
		}
		else if (temp == 'E') {
			GotoXY(start.x, h0 + h + 12);
			cout << "Exiting...";
			Sleep(1000);
			return;
		}
		else if (temp == 'S') {
			clearRow(5, h0 + h + 4, h0 + h + 7);

			GotoXY(left, h0 + h + 4);
			cout << "[D]ark Mode";
			GotoXY(left, h0 + h + 5);
			cout << "[L]evel";
			GotoXY(left, h0 + h + 6);
			cout << "[B]ack";

			char set = '0';
			while (set != 'D' && set != 'L' && set != 'B') {
				set = toupper(_getch());

				if (set == 'D') {
					GotoXY(start.x, h0 + h + 12);
					if (DARK_MODE) cout << "Dark mode deactivated!";
					else cout << "Dark mode activated!";
					DARK_MODE = 1 - DARK_MODE;
					Sleep(1000);
					clearRow(start.x - 1, h0 + h + 12);
					//drawLoading(h0 + 3);
					//resetGame();
					//startGame();
					set = '0';
				}
				else if (set == 'L') {
					int lv;
					GotoXY(start.x, h0 + h + 12);
					cout << "Start at level (1 - 3): ";
					cin >> lv;
					if (lv > 3) lv = 3;
					else if (lv < 1) lv = 1;
					Sleep(1000);
					clearRow(start.x - 1, h0 + h + 12);
					//drawLoading(h0 + 3);
					m_level = lv;
					//resetGame();
					//startGame();
					set = '0';
				}
				else if (set == 'B') {
					initGame();
				}
			}
		}
	}
}

void CGame::startGame() {
	system("cls");
	drawBorder();
	drawMenu();
	m_trafficLight.draw();
	p.draw("X");
	drawObstacle();
	STATE = 1;
	playGame();
}

void CGame::spawnObstacle() {
	m_obs.clear();

	srand((int)time(NULL));

	int dir = 0;
	int speed;
	int space = WIDTH_BOARD / m_level;

	for (int i = 0; i < NOBSTACLES; i++) {
		int x = rand() % WIDTH_BOARD;

		dir = 1 - dir;
		speed = 100 * (1 + m_level) / m_level;

		while (true) {
			x = rand() % WIDTH_BOARD + 1;
			int j = (i >= 3) ? i - 3 : 0;
			while (j <= i - 1 && abs(m_obs[m_level*j]->getPos().x - x) > 5) j++;
			if (j == i) break;
		}

		int j = 0;
		CObstacle *t;
		while (j < m_level) {
			if (dir == 1) t = new CVehicle({ (x + space*j) % WIDTH_BOARD + 1, i*LANE_HEIGHT + 2 }, dir, speed);
			else t = new CAnimal({ (x + space*j) % WIDTH_BOARD + 1, i*LANE_HEIGHT + 2 }, dir, speed);
			m_obs.push_back(t);
			j++;
		}
	}
}

void CGame::resetGame() {
	spawnObstacle();
	p = CPlayer(WIDTH_BOARD / 2, HEIGHT_BOARD);
	m_trafficLight = CTrafficLight();
	STATE = STATE_PLAYING;
}

void CGame::getKey() {
	if (STATE != STATE_PAUSED) {
		if (isPressed(KEY_P))
			pauseGame();
		else if (isPressed(KEY_ESC)) {
			exitGame();
		}
		else if (isPressed(KEY_L)) {
			pauseGame();
			saveGame();
		}
		else if (isPressed(KEY_T)) {
			STATE = 4;
		}
	}
	if (STATE == STATE_PAUSED) {
		if (isPressed(KEY_U))
			STATE = STATE_PLAYING;
	}
}

void CGame::pauseGame() {
	STATE = STATE_PAUSED;
}

void CGame::endGame() {
	p.kill();

	clearRow(1, HEIGHT_CONSOLE + 5);
	GotoXY(2, HEIGHT_CONSOLE + 5);

	cout << "Do you want to replay? [Y]es / [N]o";

	ClearConsoleInputBuffer();
	char tmp = 0;
	while (tmp != 'Y' && tmp != 'N') tmp = toupper(_getch());
	if (tmp == 'Y') {
		m_level = 1;
		resetGame();
		startGame();
	}
	else
		exitGame();

}

void CGame::levelUp() {
	clearRow(1, HEIGHT_CONSOLE + 5);
	GotoXY(2, HEIGHT_CONSOLE + 5);
	cout << "Level Up! Waiting...";
	m_level++;
	Sleep(1000);
	resetGame();
	startGame();
}

void CGame::exitGame() {
	STATE = -1;
	clearRow(1, HEIGHT_CONSOLE + 5);
	GotoXY(2, HEIGHT_CONSOLE + 5);
	cout << "Exiting...";
	Sleep(1000);
}

void CGame::drawBorder() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int x = 0, y = 0;
	int width = WIDTH_CONSOLE;
	int height = HEIGHT_CONSOLE;

	SetConsoleTextAttribute(hConsole, 14);

	GotoXY(x, y);
	cout << CORNER;
	for (int i = 1; i < width - 1; i++)
		cout << HOR_BORDER;
	cout << CORNER;

	GotoXY(x, height + y - 1);
	cout << CORNER;
	for (int i = 1; i < width - 1; i++)
		cout << HOR_BORDER;
	cout << CORNER;

	for (int i = y + 1; i < height + y + 6; i++) {
		if (i == height + y - 1)
			continue;
		GotoXY(x, i);
		cout << VER_BORDER;

		GotoXY(x + width - 1, i);
		cout << VER_BORDER;
	}

	GotoXY(x, height + y + 4);
	cout << CORNER;
	for (int i = 1; i < width - 1; i++)
		cout << HOR_BORDER;
	cout << CORNER;

	GotoXY(x, height + y + 6);
	cout << CORNER;
	for (int i = 1; i < width - 1; i++)
		cout << HOR_BORDER;
	cout << CORNER;

	GotoXY(0, 0);
	SetConsoleTextAttribute(hConsole, 15);
}

void CGame::drawLoading(int y) {
	SetColor(LIGHTGREEN);

	int width = 50;
	int height = 5;

	POINT start = { WIDTH_CONSOLE / 2 - strlen("LOADING") / 2, HEIGHT_CONSOLE / 2 - height / 2 - 1 + y };
	GotoXY(start.x, start.y);
	cout << "LOADING";

	start = { WIDTH_CONSOLE / 2 - width / 2, HEIGHT_CONSOLE / 2 - height / 2 + y };
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			GotoXY(start.x + i, start.y + j);
			cout << ".";
		}
	}

	SetColor(YELLOW);
	int count = 0;
	start = { WIDTH_CONSOLE / 2 - 40 / 2, HEIGHT_CONSOLE / 2 + y};
	for (int j = 0; j < 40; j++) {
		Sleep(800 / ++count);
		GotoXY(start.x + j, start.y);
		cout << ">";
	}
	Sleep(1000);

	SetColor(WHITE);
}

void CGame::drawMenu() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int x = 0, y = 0;
	int width = WIDTH_CONSOLE;
	int height = HEIGHT_CONSOLE;

	SetConsoleTextAttribute(hConsole, 15);
	clearRow(x, height + y, height + y + 3);
	GotoXY(x + 2, height + y);
	cout << "Press [L] to Save game." << endl;
	GotoXY(x + 2, height + y + 1);
	cout << "Press [T] to Load game." << endl;
	GotoXY(x + 2, height + y + 2);
	cout << "Press [P] to Pause game." << endl;
	GotoXY(x + 2, height + y + 3);
	cout << "Press Esc to Quit game." << endl;
	clearRow(x, height + y + 5);

	GotoXY(width + 5, height / 2);
	cout << "LEVEL #" << m_level;
}

void CGame::drawObstacle() {
	for (int i = 0; i < m_obs.size(); i++) 
		m_obs[i]->draw("O", p.getPos(), DARK_MODE);
}

void CGame::updateObstacle() {
	Sleep(200 / m_level);
	for (int i = 0; i < m_obs.size(); i++) {
		if (STATE == STATE_DEAD || STATE == STATE_PAUSED || STATE == STATE_LOAD) return;
		m_obs[i]->update(p.getPos(), DARK_MODE);
		if (STATE && m_obs[i]->isCollided(p.getPos())) { STATE = 0; break; }
	}
}

void CGame::playGame() {
	thread dr = updatePlayerThread();
	thread gk = getKeyThread();
	thread upd = updateObstacleThread();
	thread light = updateTrafficLight();
	while (true) {
		if (STATE == STATE_DEAD || STATE == STATE_ESC || STATE == STATE_WIN || STATE == STATE_LOAD) 
			break;
	}
	upd.join();
	gk.join();
	dr.join();
	light.join();

	if (STATE == STATE_DEAD) endGame();
	if (STATE == STATE_WIN) levelUp();
	if (STATE == STATE_LOAD) loadGame();
}

void CGame::saveGame() {
	drawTurn.lock();

	GotoXY(strlen("Press [L] to Save game.") + 3, HEIGHT_CONSOLE);
	char *filename = new char[100];
	cout << "Input file name: ";

	ClearConsoleInputBuffer();
	cin >> filename;

	FILE* f = fopen(filename, "wb");
	//fprintf(f, "%d %d %d\n", m_level, m_trafficLight.isGreen(), m_obs.size());
	int green = m_trafficLight.isGreen();
	int size = m_obs.size();

	fwrite(&m_level, sizeof(m_level), 1, f);
	fwrite(&DARK_MODE, sizeof(DARK_MODE), 1, f);
	fwrite(&green, sizeof(green), 1, f);
	fwrite(&size, sizeof(size), 1, f);

	p.save(f);
	for (int i = 0; i < m_obs.size(); i++) m_obs[i]->save(f);
	fclose(f);
	delete filename;

	GotoXY(2, HEIGHT_CONSOLE + 5);
	cout << "Successfully saved! Press [U]npause to play.";
	Sleep(1500);

	drawMenu();

	drawTurn.unlock();
}

void CGame::loadGame(bool menu) {
	char *filename = new char[100];
	FILE *f;

	if (menu) {
		GotoXY(14, 20);
		cout << "Input file name: ";

		ClearConsoleInputBuffer();
		cin >> filename;

		f = fopen(filename, "rb");
		
		if (f == NULL) {
			clearRow(10, 20);
			GotoXY(14, 20);
			cout << "Loaded failed! Game will start shortly...";
			resetGame();
		}
		drawLoading(6);
	}
	else {
		GotoXY(strlen("Press [T] to Load game.") + 3, HEIGHT_CONSOLE + 1);
		char *filename = new char[100];
		cout << "Input file name: ";

		ClearConsoleInputBuffer();
		cin >> filename;

		f = fopen(filename, "rb");
		GotoXY(2, HEIGHT_CONSOLE + 5);
		if (f == NULL) {
			cout << "Loaded failed!";
		}
		else {
			drawLoading();
		}
	}

	if (f != NULL) {
		int size;
		int green;

		fread(&m_level, sizeof(m_level), 1, f);
		fread(&DARK_MODE, sizeof(DARK_MODE), 1, f);
		fread(&green, sizeof(green), 1, f);
		fread(&size, sizeof(size), 1, f);

		m_trafficLight.isGreen() = green;

		//fscanf(f, "%d %d %d\n", &m_level, &m_trafficLight.isGreen(), &obs_size);
		p.load(f);

		m_obs.clear();
		m_obs.resize(size);

		for (int i = 0; i < m_obs.size(); i++) {
			//char type;
			//int x, y, dir, speed;

			//fscanf(f, "%c %d %d %d %d\n", &type, &x, &y, &dir, &speed);
			char type;
			POINT p;
			int dir;
			int speed;

			fread(&type, sizeof(type), 1, f);
			fread(&p, sizeof(p), 1, f);
			fread(&dir, sizeof(dir), 1, f);
			fread(&speed, sizeof(speed), 1, f);

			if (type == 'A') m_obs[i] = new CAnimal(p, dir, speed);
			if (type == 'V') m_obs[i] = new CVehicle(p, dir, speed);
		}

		fclose(f);
	}

	delete filename;
	startGame();
}

thread CGame::getKeyThread() {
	return thread([=] {
		while (true) {
			if (STATE == STATE_PLAYING || STATE == STATE_PAUSED) {
				getKey();
			}
			else {
				break;
			}
		}
	});
}

thread CGame::updateObstacleThread() {
	return thread([=] {
		while (true) {
			if (STATE == STATE_ESC || STATE == STATE_DEAD || STATE == STATE_WIN || STATE == STATE_LOAD) break;
			if (STATE != STATE_PAUSED) {
				if (m_trafficLight.isGreen()) updateObstacle();
				else drawObstacle();
			}
		}
	});
}

thread CGame::updatePlayerThread() {
	return thread([=] {
		while (true) {
			if (STATE == STATE_PLAYING) {
				p.update();
				if (p.isDone()) {
					STATE = STATE_WIN;
					break;
				}
				drawTurn.lock();
				for (int i = 0; i < m_obs.size(); i++)
					if (STATE && m_obs[i]->isCollided(p.getPos())) {
						STATE = 0;
						break;
					}
				drawTurn.unlock();
			}

			if (STATE == STATE_DEAD || STATE == STATE_ESC || STATE == STATE_WIN || STATE == 4) break;
		}
	});
}

thread CGame::updateTrafficLight() {
	return thread([=] {
		chrono::steady_clock::time_point begin = chrono::high_resolution_clock::now();
		while (true) {
			if (STATE == STATE_PLAYING) {
				if (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin).count() == 15) {
					m_trafficLight.switchLight();
					m_trafficLight.draw();
					begin = chrono::high_resolution_clock::now();
				}
			}

			if (STATE == STATE_PAUSED) begin = chrono::high_resolution_clock::now();

			if (STATE == STATE_DEAD || STATE == STATE_ESC || STATE == STATE_WIN || STATE == 4) break;
		}
	});
}