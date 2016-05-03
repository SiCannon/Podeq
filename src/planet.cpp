#include <math.h>
#include <GL/freeglut.h>
#include "planet.h"
#include "defines.h"

Planet::Planet(GLfloat mass) : BaseActor()
{
	this->mass = mass;
}

/*
Planet::~Planet()
{
}*/

#define SLICES 48

void Planet::draw_me()
{
	//GLfloat outerRadius = 0.3f;
	//GLfloat crustThickness = 0.05f;

	GLfloat outerRadius = 1.0f;
	GLfloat crustThickness = 0.3f;

	GLfloat innerRadius = outerRadius - crustThickness;
	

	glColor3ub(192, 0, 192);

	glBegin(GL_TRIANGLE_STRIP);

	for (int t = 0; t <= SLICES; t++)
	{
		GLfloat theta = ((GLfloat)t / (GLfloat)SLICES) * 6.284;
		GLfloat x = innerRadius * sin(theta);
		GLfloat y = innerRadius * cos(theta);
		glColor3ub(64, 0, 64);
		glVertex2f(x, y);
		x = outerRadius * sin(theta);
		y = outerRadius * cos(theta);
		glColor3ub(192, 0, 192);
		glVertex2f(x, y);
	}

	glEnd();
    
    glColor3ub(64, 0, 64);
    
	glBegin(GL_TRIANGLE_FAN);
    
    glVertex2f(0, 0);
    
    for (int t = 0; t <= SLICES; t++)
    {
        GLfloat theta = ((GLfloat)t / (GLfloat)SLICES) * 6.284;
		GLfloat x = innerRadius * sin(theta);
		GLfloat y = innerRadius * cos(theta);
        glVertex2f(x, y);
    }
    
	glEnd();
}

GLfloat Planet::GM()
{
	return mass * GravConstant;
}