#pragma once

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <atomic>
using namespace std;
#include "Constants.h"

void fixConsoleWindow();
void hideCursor();
void GotoXY(int x, int y);
bool isPressed(int key);

extern mutex drawTurn;

void pressEnter();
void ClearConsoleInputBuffer();
void clearRow(int startX, int startY, int endY = -1, int len = 10);

void SetColor(int);