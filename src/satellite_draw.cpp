#include <GL/freeglut.h>
#include <include/shapes.h>
#include "satellite_draw.h"
#include "satellite.h"

SatelliteDraw::SatelliteDraw(Satellite *satellite, glf radius, GLubyte red, GLubyte green, GLubyte blue)
{
	this->satellite = satellite;
	this->radius = radius;
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void SatelliteDraw::draw()
{
	glPushMatrix();
	glTranslatef(satellite->position.x, satellite->position.y, 0);
	glColor3ub(red, green, blue);
	glSolidCircle(radius, 48);

	glColor3ub(red / 4, green / 4, blue / 4);

	glf r = satellite->sphere_of_influence();
	glOpenEllipse(r, r, 48);

	glPopMatrix();
}