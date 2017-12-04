#include "Obstacle.h"

mutex drawTurn;

void CObstacle::draw(string s, POINT p, bool dark) {
	for (int i = 0; i < m_key.size(); i++) {
		for (int j = 0; j < m_key[i].size(); j++) {
			int x = (m_pos.x + j) % WIDTH_BOARD + 1;
			int y = m_pos.y + i;
			GotoXY(x, y);
			if (s != " ") {
				if (!dark || (abs(x - p.x) <= 3 && abs(y - p.y) <= 3)) cout << m_key[i][j];
			}
			else cout << s;
		}
	}
}

void CObstacle::update(POINT p, bool dark) {
	draw(" ", p, dark);
	if (m_dir) m_pos.x = (m_pos.x) % WIDTH_BOARD + 1;
	else m_pos.x = (WIDTH_BOARD + m_pos.x - 2) % WIDTH_BOARD + 1;
	//if (abs(m_pos.y - p.y) <= 5 && abs(m_pos.x - p.x) <= 10) 
	draw("a", p, dark);
}

void CObstacle::save(FILE* f) {
	//fprintf(f, "%d %d %d %d\n", m_pos.x, m_pos.y, m_dir, m_speed);
	fwrite(&m_pos, sizeof(m_pos), 1, f);
	fwrite(&m_dir, sizeof(m_dir), 1, f);
	fwrite(&m_speed, sizeof(m_speed), 1, f);
}