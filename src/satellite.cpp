#include <include/gaf.h>
//#include "has_position.h"
//#include "has_position_and_velocity.h"
#include "defines.h"
#include "satellite.h"
#include "orbit.h"

//Satellite::Satellite(HasPosition *parent) : HasPositionAndVelocity()
//{
//	this->parent = parent;
//	this->orbit = new Orbit(0, 0);
//}


Satellite::Satellite(Satellite *parent, glf mass)
{
	this->parent = parent;
	this->mass = mass;
	//this->orbit = new Orbit(parent, this);
}

glf Satellite::GM()
{
	return GravConstant * mass;
}