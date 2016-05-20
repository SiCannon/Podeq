#pragma once

#include <include/gaf.h>
#include <include/vector2f.h>


//#include "has_position.h"
//#include "has_position_and_velocity.h"

class Orbit;

/*class Satellite : public HasPositionAndVelocity
{
public:
	Satellite(HasPosition *parent);
private:
	glf mass;
	HasPosition *parent;
	Orbit *orbit;
};*/


class Satellite
{
public:
	Satellite(Satellite *parent, glf mass);
	Vector2f position;
	Vector2f velocity;
	glf mass;
	glf GM();
private:
	Satellite *parent;
	//Orbit *orbit;
};