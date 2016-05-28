#pragma once

#include <include/gaf.h>
#include <include/update_task.h>
#include <include/timer.h>
#include <include/vector2f.h>

#include "defines.h"
#include "satellite.h"

class Ship2;
class Planet;

class Orbit : public UpdateTask
{
public:
#ifdef use_satellites
	Orbit(Satellite *parent, Satellite *child);
#else
	Orbit(Planet *planet, Ship2 *ship);
#endif

    glf Rp;
	glf Ra;
	glf nu;
	glf angle;
	glf e;
	glf a;
	glf mean_motion;
	bool is_clockwise;

	glf debug;

    void calc(glf rx, glf ry, glf vx, glf vy, glf GM);
    void calc(glf planet_x, glf planet_y, glf ship_x, glf ship_y, glf vx, glf vy, glf GM);
	void calc();
	void update(Timer *timer);
	bool is_hyperbolic();
	Vector2f position_at_time(glf t);

	Vector2f position_p;
	GLfloat position_phi;
	GLfloat position_speed;
	GLfloat position_theta;
	Vector2f position_v;
	void calc_position(GLfloat t);

	Satellite *get_parent();

	void set_parent(Satellite *parent);
private:
#ifdef use_satellites
	Satellite *parent;
	Satellite *child;
#else
	Planet *planet;
	Ship2 *ship;
#endif
};