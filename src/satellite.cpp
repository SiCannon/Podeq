#include <include/gaf.h>
//#include "has_position.h"
//#include "has_position_and_velocity.h"
#include "defines.h"
#include "satellite.h"
#include "orbit.h"
#include "warp.h"

//Satellite::Satellite(HasPosition *parent) : HasPositionAndVelocity()
//{
//	this->parent = parent;
//	this->orbit = new Orbit(0, 0);
//}


Satellite::Satellite(Satellite *parent, glf mass, Warp *warp)
{
	this->parent = parent;
	this->mass = mass;
	this->warp = warp;
	this->orbit = new Orbit(parent, this);
	lastUpdateTime = 0;
}

glf Satellite::GM()
{
	return GravConstant * mass;
}

void Satellite::update(Timer * timer)
{
	glf time = timer->intervalSeconds() * warp->warp;

	glf timeSinceLastUpdate = time;
	glf newWarpedTime = lastUpdateTime + timeSinceLastUpdate;
	lastUpdateTime = newWarpedTime;

	orbit->calc_position(newWarpedTime);
	position = parent->position + orbit->position_p;
	velocity = orbit->position_v;
}

void Satellite::recalc_orbit()
{
	orbit->calc();
	lastUpdateTime = 0;
}
