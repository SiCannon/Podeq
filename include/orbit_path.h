#pragma once

#include "base_actor.h"

class OrbitPath : public BaseActor
{
public:
	OrbitPath();
	GLfloat apoapsis;
	GLfloat periapsis;
	GLfloat angle;
protected:
	void draw_me();
};
