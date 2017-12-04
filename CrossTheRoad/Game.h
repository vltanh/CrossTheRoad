#pragma once

#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include "Player.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "TrafficLight.h"

class CGame : protected GameWindow {
private:
	atomic<int> STATE;
	bool DARK_MODE;

	int m_level;

	CPlayer p;
	vector<CObstacle*> m_obs;
	CTrafficLight m_trafficLight;
	GameWindow* m_wnd;
public:
	CGame();
	~CGame();

	void initGame();
	void startGame();
	void playGame();
	void resetGame();
	void pauseGame();
	void endGame();
	void exitGame();
	void saveGame();
	void loadGame(bool = false);

	void levelUp();

	void getKey();

	void drawMenu();
	void drawBorder();
	void drawObstacle();
	void drawLoading(int = 0);

	void spawnObstacle();
	void updateObstacle();

	thread getKeyThread();
	thread updateObstacleThread();
	thread updatePlayerThread();
	thread updateTrafficLight();
};

#endif