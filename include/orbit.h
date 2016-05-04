#pragma once

#include <GL/freeglut.h>
#include <include/update_task.h>
#include <include/timer.h>
#include "planet.h"
#include "ship.h"

class Orbit : public UpdateTask
{
public:
    Orbit(Planet *planet, Ship *ship);
    GLfloat Rp;
    GLfloat Ra;
    GLfloat nu;
    GLfloat angle;
    void calc(GLfloat rx, GLfloat ry, GLfloat vx, GLfloat vy, GLfloat GM);
    void calc(GLfloat planet_x, GLfloat planet_y, GLfloat ship_x, GLfloat ship_y, GLfloat vx, GLfloat vy, GLfloat GM);
	void calc();
	void update(Timer *timer);
private:
	Planet *planet;
	Ship *ship;
};