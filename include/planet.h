#pragma once

#include <include/base_actor.h>

class Planet : public BaseActor
{
public:
	Planet(GLfloat mass);
	GLfloat mass;
	GLfloat GM();
protected:
	void draw_me();
};
