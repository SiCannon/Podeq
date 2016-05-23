#pragma once

#include <include/base_actor.h>
#include <include/draw_task.h>
#include "satellite.h"

class Warp;

class Planet : public DrawTask, public Satellite
{
public:
	Planet(GLfloat mass, Warp *warp);
	//GLfloat mass;
	//GLfloat GM();
	GLfloat radius;
	void draw();
protected:
	void draw_me();
};
