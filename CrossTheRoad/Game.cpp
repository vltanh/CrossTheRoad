#include "Game.h"
#include "Animal.h"
#include "Vehicle.h"

mutex a;

CGame::CGame() : GameWindow() {
	p = CPlayer(WIDTH_BOARD / 2, HEIGHT_BOARD);
	m_level = 1;
}

CGame::~CGame()
{
	for (int i = 0; i < m_obs.size(); i++)
		delete m_obs[i];
}

void CGame::initGame() {
	cout << "Welcome to: CROSS THE ROAD!" << endl;
	cout << "* [N]ew Game" << endl;
	cout << "* [L]oad Game" << endl;
	cout << "* [S]ettings" << endl;
	char temp = 0;
	while (temp != 'L' && temp != 'S' && temp != 'N') {
		temp = toupper(_getch());
		if (temp == 'N') {
			cout << "Starting...";
			Sleep(1500);
			resetGame();
			startGame();
		}
		else if (temp == 'L') {
			cout << "Loading...";
			Sleep(1500);
			loadGame(true);
		}
		else if (temp == 'S') {
			cout << "This feature is not yet implemented. \nThe game will start shortly...";
			Sleep(1500);
			resetGame();
			startGame();
		}
	}
}

void CGame::startGame() {
	system("cls");
	drawBorder();
	drawMenu();
	m_trafficLight.draw();
	p.draw("X");
	updateObstacle();
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
	STATE = 1;
	spawnObstacle();
	p = CPlayer(WIDTH_BOARD / 2, HEIGHT_BOARD);
	m_trafficLight = CTrafficLight();
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
			//STATE = 4;
			saveGame();
		}
		else if (isPressed(KEY_T)) {
			//pauseGame();
			STATE = 4;
			//loadGame();
		}
	}
}

void CGame::pauseGame() {
	STATE = 2;
}

void CGame::endGame() {
	//p.draw("X", 0);
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
}

void CGame::drawObstacle() {
	for (int i = 0; i < m_obs.size(); i++) 
		m_obs[i]->draw("O");
}

void CGame::updateObstacle() {
	this_thread::sleep_for(200ms / m_level);
	for (int i = 0; i < m_obs.size(); i++) {
		if (STATE == 0) return;

		m_obs[i]->update(p.getPos());
		
		/*if (STATE) {
			for (int j = 0; j < 3 && STATE; j++) {
				for (int k = 0; k < 3; k++) {
					int x = (m_obs[i]->getPos().x + j) % WIDTH_BOARD + 1;
					int y = m_obs[i]->getPos().y + k;

					if (p.isCollided({ x, y })) { STATE = 0; break; }
				}
			}
		}*/

		//if (STATE && p.isCollided(m_obs[i]->getPos())) { STATE = 0; break; }
		if (STATE && m_obs[i]->isCollided(p.getPos())) { STATE = 0; break; }
	}
}

void CGame::playGame() {
	thread dr = updatePlayerThread();
	thread gk = getKeyThread();
	thread upd = updateObstacleThread();
	thread light = updateTrafficLight();
	while (true) {
		if (STATE == 1) {
			
		}
		else if (STATE == 2) {
			switch (toupper(_getch()))
				case 'U': STATE = 1;
		}
		else if (STATE == 0 || STATE == -1) {
			break;
		}
		else if (STATE == 3) {
			break;
		}
		else if (STATE == 4) {
			break;
		}
	}
	upd.join();
	gk.join();
	dr.join();
	light.join();

	if (STATE == 0) endGame();
	if (STATE == 3) levelUp();
	if (STATE == 4) loadGame();
}

void CGame::saveGame() {
	drawTurn.lock();

	GotoXY(strlen("Press [L] to Save game.") + 3, HEIGHT_CONSOLE);
	ClearConsoleInputBuffer();
	//char *filename = new char[100];
	//cout << "Input file name: ";
	//cin >> filename;
	char filename[] = "hello";
	strcat(filename, ".txt");

	FILE* f = fopen(filename, "w");
	fprintf(f, "%d %d %d\n", m_level, m_trafficLight.isGreen(), m_obs.size());
	fclose(f);

	p.save(filename);
	for (int i = 0; i < m_obs.size(); i++) m_obs[i]->save(filename);

	f = fopen("HELLO.SAV", "wb");
	fwrite(this, sizeof(*this), 1, f);
	fclose(f);

	GotoXY(2, HEIGHT_CONSOLE + 5);
	cout << "Successfully saved! Press [U]npause to play.";
	Sleep(2000);

	drawMenu();

	drawTurn.unlock();
}

void CGame::loadGame(bool menu) {
	FILE *f = fopen("hello.txt", "r");
	
	int obs_size;
	fscanf(f, "%d %d %d\n", &m_level, &m_trafficLight.isGreen(), &obs_size);
	p.load(f);
	m_obs.clear();
	m_obs.resize(obs_size);

	for (int i = 0; i < m_obs.size(); i++) {
		char type;
		int x, y, dir, speed;
		
		fscanf(f, "%c %d %d %d %d\n", &type, &x, &y, &dir, &speed);
		if (type == 'A') m_obs[i] = new CAnimal({ x,y }, dir, speed);
		if (type == 'V') m_obs[i] = new CVehicle({ x,y }, dir, speed);
	}

	fclose(f);

	if (!menu) {
		GotoXY(2, HEIGHT_CONSOLE + 5);
		cout << "Loading...";
		Sleep(1000);
	}

	startGame();
}

thread CGame::getKeyThread() {
	return thread([=] {
		bool flag = true;
		while (flag) {
			switch (STATE) {
			case STATE_PLAYING:
				getKey(); break;
			case STATE_PAUSED:
				break;
			default:
				flag = false; break;
			}
		}
	});
}

thread CGame::updateObstacleThread() {
	return thread([=] {
		while (true) {
			if (STATE == STATE_ESC || STATE == STATE_DEAD || STATE == STATE_WIN || STATE == 4) break;
			else if (STATE != STATE_PAUSED && m_trafficLight.isGreen()) updateObstacle();
		}
	});
}

thread CGame::updatePlayerThread() {
	return thread([=] {
		while (true) {
			if (STATE == STATE_PLAYING) {
				p.update();
				if (p.isDone()) {
					STATE = 3;
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