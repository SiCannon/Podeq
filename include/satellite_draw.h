#pragma once

#include <GL/freeglut.h>
#include <include/gaf.h>
#include <include/draw_task.h>

class Satellite;

class SatelliteDraw : public DrawTask
{
public:
	SatelliteDraw(Satellite *satellite, glf radius, GLubyte red, GLubyte green, GLubyte blue);
	void draw();
private:
	Satellite *satellite;
	glf radius;
	GLubyte red;
	GLubyte green;
	GLubyte blue;
};