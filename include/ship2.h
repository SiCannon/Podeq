#pragma once

#include <include/entity.h>
#include <include/vector2f.h>
#include <include/update_task.h>
#include <include/input_task.h>
#include <include/timer.h>
#include <include/keyboard.h>

class PodeqGame;

class Ship2 : public Entity, public UpdateTask, public InputTask
{
public:
	Vector2f v;
	Ship2(PodeqGame *game, Vector2f pos, Vector2f vel);
	void update(Timer *timer);
	void input(Keyboard *keyboard);
	glf speed();
private:
	PodeqGame *game;
	
	bool isThrust;
	void create_ship();
};