#pragma once

#include <GL/freeglut.h>
#include <include/update_task.h>
#include <include/timer.h>
#include "planet.h"

class Ship2;

class Orbit : public UpdateTask
{
public:
    Orbit(Planet *planet, Ship2 *ship);
    GLfloat Rp;
    GLfloat Ra;
    GLfloat nu;
    GLfloat angle;
	GLfloat e;
    void calc(GLfloat rx, GLfloat ry, GLfloat vx, GLfloat vy, GLfloat GM);
    void calc(GLfloat planet_x, GLfloat planet_y, GLfloat ship_x, GLfloat ship_y, GLfloat vx, GLfloat vy, GLfloat GM);
	void calc();
	void update(Timer *timer);
	bool is_hyperbolic();
private:
	Planet *planet;
	Ship2 *ship;
};