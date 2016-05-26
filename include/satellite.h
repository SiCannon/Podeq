#pragma once

#include <include/gaf.h>
#include <include/vector2f.h>
#include <include/update_task.h>
#include <include/timer.h>

//#include "has_position.h"
//#include "has_position_and_velocity.h"

class Orbit;
class Warp;

/*class Satellite : public HasPositionAndVelocity
{
public:
	Satellite(HasPosition *parent);
private:
	glf mass;
	HasPosition *parent;
	Orbit *orbit;
};*/


class Satellite : public UpdateTask
{
public:
	Satellite(Satellite *parent, glf mass, Warp *warp);
	Vector2f position;
	Vector2f velocity;
	glf mass;
	glf GM();
	void update(Timer *timer);
	void recalc_orbit();
	Warp *warp;
	Orbit *get_orbit();
protected:
	Satellite *parent;
	glf lastUpdateTime;
private:
	Orbit *orbit;
};