#include <math.h>
#include <GL/freeglut.h>
#include "ellipse.h"
#include <include/gaf_math.h>

Podeq::Ellipse::Ellipse(Timer *timer) : BaseActor()
{
	xradius = 6.0f;
	yradius = 5.0f;
}

#define SLICES 48

void Podeq::Ellipse::draw_me()
{

	glColor3ub(192, 0, 192);

	glBegin(GL_LINE_LOOP);

	for (int t = 0; t <= SLICES; t++)
	{
		GLfloat theta = ((GLfloat)t / (GLfloat)SLICES) * TWO_PI;
		GLfloat x = xradius * cosf(theta);
		GLfloat y = yradius * sinf(theta);
		glVertex2f(x, y);
	}

	glEnd();
	
	glColor3ub(0, 192, 0);
	
	glBegin(GL_POINTS);
	
	GLfloat a = fmaxf(xradius, yradius);
	GLfloat b = fminf(xradius, yradius);
	GLfloat f = sqrtf(powf(a, 2.0) - powf(b, 2.0));
	
	glVertex2f(f, 0);
	glVertex2f(-f, 0);
	
	glEnd();
}
