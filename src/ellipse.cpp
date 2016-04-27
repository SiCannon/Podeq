#include <math.h>
#include <GL/freeglut.h>
#include "ellipse.h"

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
		GLfloat theta = ((GLfloat)t / (GLfloat)SLICES) * 6.284;
		GLfloat x = xradius * cos(theta);
		GLfloat y = yradius * sin(theta);
		glVertex2f(x, y);
	}

	glEnd();
	
	glColor3ub(0, 192, 0);
	
	glBegin(GL_POINTS);
	
	GLfloat a = fmax(xradius, yradius);
	GLfloat b = fmin(xradius, yradius);
	GLfloat f = sqrt(pow(a, 2.0) - pow(b, 2.0));
	
	glVertex2f(f, 0);
	glVertex2f(-f, 0);
	
	glEnd();
}
