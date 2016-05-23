#pragma once

#include <include/gaf.h>
#include <include/input_task.h>
#include <include/update_task.h>
#include <include/keyboard.h>
#include <include/timer.h>

class Warp : public InputTask, public UpdateTask
{
public:
	Warp();
	void input(Keyboard *keyboard);
	void update(Timer *timer);
	glf warp;
private:
	int warp_change_direction;
	bool increase_warp;
	bool decrease_warp;
	bool reset_warp;
};