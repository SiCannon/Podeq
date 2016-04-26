#pragma once

#include <vector>
#include "timer.h"
#include "include/draw_task.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void loop();
	void register_drawTask(DrawTask *task);
private:
	Timer *timer;
	std::vector<DrawTask*> drawTasks;
	void input();
	void update();
	void display();
};

extern GameEngine *gameEngine;
void main_game_loop();