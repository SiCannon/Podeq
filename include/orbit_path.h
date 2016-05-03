#pragma once

#include <include/base_actor.h>
#include "orbit.h"

class OrbitPath : public BaseActor
{
public:
	OrbitPath(Orbit *orbit);
	/*GLfloat apoapsis;
	GLfloat periapsis;
	GLfloat angle;*/
protected:
	void draw_me();
private:
	Orbit *orbit;
};
