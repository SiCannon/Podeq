#pragma once

#include "timer.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void loop();
private:
	Timer *timer;
	void input();
	void update();
	void display();
};

extern GameEngine *gameEngine;
void main_game_loop();