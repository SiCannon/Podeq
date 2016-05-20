#pragma once

#include <include/entity.h>
#include <include/vector2f.h>
#include <include/gaf.h>
#include <include/update_task.h>
#include <include/input_task.h>
#include <include/timer.h>
#include <include/keyboard.h>

class PodeqGame;

class Ship2 : public Entity, public UpdateTask, public InputTask
{
public:
	Ship2(PodeqGame *game, Vector2f pos, Vector2f vel);

	void update(Timer *timer);
	void input(Keyboard *keyboard);
	glf speed();

	Vector2f v;
	glf warp;
private:
	
	void create_ship();
	bool isWarp();

	PodeqGame *game;
	bool isThrust;
	bool wasThrust;
	glf lastUpdateTime;
};