#pragma once

#include <vector>
#include <include/input_task.h>
#include <include/update_task.h>
#include <include/keyboard.h>
#include <include/timer.h>
#include <include/keydown_handler.h>

class Ship2;
class Planet;
class Satellite;

class Camera : public InputTask, public UpdateTask, public Keydown_Handler
{
public:
	Camera(Ship2 *ship, Planet *planet);
	Camera();
	void add_satellite(Satellite *s);
	void input(Keyboard *keyboard);
	void update(Timer *timer);
	void on_keydown(int key, bool is_special);
private:
	bool new_style;
	std::vector<Satellite*> satellites;
	Ship2 *ship;
	Planet *planet;
	short focus;
};