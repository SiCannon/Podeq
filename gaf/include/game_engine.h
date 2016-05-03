#pragma once

#include <vector>
#include "timer.h"
#include <include/draw_task.h>
#include "include/update_task.h"
#include "include/input_task.h"
#include "keyboard.h"
#include <include/transform.h>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void loop();
	void register_inputTask(InputTask *task);
	void register_updateTask(UpdateTask *task);
	void register_drawTask(DrawTask *task);
	Keyboard *keyboard;
	Transform *world_transform;
private:
	Timer *timer;
	std::vector<InputTask*> inputTasks;
	std::vector<UpdateTask*> updateTasks;
	std::vector<DrawTask*> drawTasks;
	void input();
	void update();
	void display();
};

extern GameEngine *gameEngine;
void main_game_loop();