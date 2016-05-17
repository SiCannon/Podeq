#pragma once

#include <include/input_task.h>
#include <include/update_task.h>
#include <include/keyboard.h>
#include <include/timer.h>
#include <include/keydown_handler.h>

class Ship2;
class Planet;

class Camera : public InputTask, public UpdateTask, public Keydown_Handler
{
public:
	Camera(Ship2 *ship, Planet *planet);
	void input(Keyboard *keyboard);
	void update(Timer *timer);
	void on_keydown(int key, bool is_special);
private:
	Ship2 *ship;
	Planet *planet;
	short focus;
};