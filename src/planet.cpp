#include <math.h>
#include <GL/freeglut.h>
#include "planet.h"
#include "defines.h"
#include <include/shapes.h>

Planet::Planet(GLfloat mass) : BaseActor()
{
	this->mass = mass;
}

/*
Planet::~Planet()
{
}*/

#define SLICES 200

void Planet::draw_me()
{
	//GLfloat outerRadius = 0.3f;
	//GLfloat crustThickness = 0.05f;

	GLfloat outerRadius = 1.0f;
	GLfloat crustThickness = 0.99f;

	GLfloat innerRadius = outerRadius - crustThickness;
	
	GLfloat atmosphereThickness = 0.05f;
	GLfloat outerSpaceRadius = outerRadius + atmosphereThickness;

	const GLubyte innerColor[3] = { 0, 64, 64 };
	const GLubyte outerColor[3] = { 0, 192, 192};
	const GLubyte atmoStartColor[3] = { 64, 0, 96 };
	const GLubyte atmoEndColor[3] = { 0, 0, 0 };

	glTorus(innerRadius, outerRadius, innerColor, outerColor, SLICES);
	glTorus(outerRadius, outerSpaceRadius, atmoStartColor, atmoEndColor, SLICES);

	glColor3ubv(innerColor);
	glSolidCircle(innerRadius, SLICES);
}

GLfloat Planet::GM()
{
	return mass * GravConstant;
}