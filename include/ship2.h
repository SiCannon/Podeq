#pragma once

#include <include/entity.h>
#include <include/vector2f.h>
#include <include/gaf.h>
#include <include/update_task.h>
#include <include/input_task.h>
#include <include/timer.h>
#include <include/keyboard.h>
#include "satellite.h"

class PodeqGame;
class Planet;

class Ship2 : public Entity, public UpdateTask, public InputTask, public Satellite
{
public:
	Ship2(PodeqGame *game, Satellite *orbiting, Vector2f pos, Vector2f vel, Warp *warp);

	void update(Timer *timer);
	void input(Keyboard *keyboard);
	glf speed();

	//Vector2f velocity;
	//glf warp;
private:
	
	void create_ship();
	bool isWarp();

	PodeqGame *game;
	bool isThrust;
	bool wasThrust;
	glf lastUpdateTime;
};