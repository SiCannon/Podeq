#include <GL/freeglut.h>
#include <include/shapes.h>
#include "moon_draw.h"
#include "moon.h"

MoonDraw::MoonDraw(Moon *moon, glf radius, GLubyte red, GLubyte green, GLubyte blue)
{
	this->moon = moon;
	this->radius = radius;
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void MoonDraw::draw()
{
	glPushMatrix();
	glTranslatef(moon->position.x, moon->position.y, 0);
	glColor3ub(red, green, blue);
	glSolidCircle(radius, 48);
	glPopMatrix();
}