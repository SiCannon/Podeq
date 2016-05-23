#include <GL/freeglut.h>
#include <include/shapes.h>
#include "moon_draw.h"
#include "moon.h"

MoonDraw::MoonDraw(Moon *moon)
{
	this->moon = moon;
}

void MoonDraw::draw()
{
	glPushMatrix();
	glTranslatef(moon->position.x, moon->position.y, 0);
	glColor3ub(64, 64, 192);
	glSolidCircle(0.1f, 16);
	glPopMatrix();
}