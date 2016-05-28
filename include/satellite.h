#pragma once

#include <vector>
#include <include/gaf.h>
#include <include/vector2f.h>
#include <include/update_task.h>
#include <include/timer.h>

class Orbit;
class Warp;

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
	void add_child(Satellite *child);
	Vector2f absolute_velocity();
	glf sphere_of_influence();
	Satellite *parent;
	std::vector<Satellite*> children;
protected:
	glf lastUpdateTime;
	Orbit *orbit;
private:
};