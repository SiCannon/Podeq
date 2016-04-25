#pragma once

#include "base_actor.h"

class Planet : public BaseActor
{
public:
	Planet(Timer *timer, GLfloat mass);
	GLfloat mass;
	GLfloat GM();
protected:
	void draw_me();
};
