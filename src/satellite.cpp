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

Orbit * Satellite::get_orbit()
{
	return orbit;
}

void Satellite::add_child(Satellite * child)
{
	children.push_back(child);
}

Vector2f Satellite::absolute_velocity()
{
	if (parent != NULL)
	{
		return velocity + parent->velocity;
	}
	else
	{
		return velocity;
	}
}

glf Satellite::sphere_of_influence()
{
	if (parent == NULL)
	{
		return INFINITY;
	}
	else
	{
		// http://www.braeunig.us/space/orbmech.htm equation 4.89
		return (position - parent->position).length() * powf(mass / parent->mass, 0.4f);
	}
}
