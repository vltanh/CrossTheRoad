#include "Obstacle.h"

mutex drawTurn;

void CObstacle::draw(string s) {
	for (int i = 0; i < m_key.size(); i++) {
		for (int j = 0; j < m_key[i].size(); j++) {
			int x = (m_pos.x + j) % WIDTH_BOARD + 1;
			GotoXY(x, m_pos.y + i);
			if (s != " ") cout << m_key[i][j];
			else cout << s;
		}
	}
}

void CObstacle::update(POINT p) {
	//this_thread::sleep_for(10ms / double(m_speed));

	if (STATE == 0) return;

	draw(" ");
	if (m_dir) m_pos.x = (m_pos.x) % WIDTH_BOARD + 1;
	else m_pos.x = (WIDTH_BOARD + m_pos.x - 2) % WIDTH_BOARD + 1;
	//if (abs(m_pos.y - p.y) <= 5 && abs(m_pos.x - p.x) <= 10) 
		draw("a");
}

void CObstacle::save(char* dir) {
	FILE *f = fopen(dir, "a");
	fprintf(f, "%d %d %d %d\n", m_pos.x, m_pos.y, m_dir, m_speed);
	//for (int i = 0; i < m_key.size(); i++) fprintf(f, "%s\n", m_key[i]);
	fclose(f);
}