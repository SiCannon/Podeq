#include <math.h>
#include <stdlib.h>
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

#define SLICES 1000

void Planet::draw_me()
{
	//GLfloat outerRadius = 0.3f;
	//GLfloat crustThickness = 0.05f;

	srand(Seed);

	GLfloat outerRadius = 1.0f;
	GLfloat crustThickness = 0.99f;

	GLfloat innerRadius = outerRadius - crustThickness;
	
	GLfloat atmosphereThickness = 0.05f;
	GLfloat outerSpaceRadius = outerRadius + atmosphereThickness;

	const GLubyte innerColor[3] = { 0, 64, 64 };
	const GLubyte outerColor[3] = { 0, 192, 192};
	const GLubyte atmoStartColor[3] = { 64, 0, 96 };
	const GLubyte atmoEndColor[3] = { 0, 0, 0 };

	glTorus(outerRadius, outerSpaceRadius, atmoStartColor, atmoEndColor, SLICES);

	//glTorus(innerRadius, outerRadius, innerColor, outerColor, SLICES);

	int slices = SLICES;
	glBegin(GL_TRIANGLE_STRIP);

	GLfloat variablility = 0.005f;

	GLfloat theta, x, y;
	GLfloat s = (GLfloat)slices;

	for (int t = 0; t <= slices; t++)
	{
		theta = ((GLfloat)t / s) * 6.284f;
		x = innerRadius * sin(theta);
		y = innerRadius * cos(theta);
		glColor3ubv(innerColor);
		glVertex2f(x, y);
		GLfloat r = outerRadius + (variablility * (GLfloat)rand() / RAND_MAX);
		x = r * sin(theta);
		y = r * cos(theta);
		glColor3ubv(outerColor);
		glVertex2f(x, y);
	}

	glEnd();


	

	glColor3ubv(innerColor);
	glSolidCircle(innerRadius, SLICES);

	

}

GLfloat Planet::GM()
{
	return mass * GravConstant;
}