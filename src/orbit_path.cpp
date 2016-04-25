#include <math.h>
#include <GL/freeglut.h>
#include "gaf_math.h"
#include "orbit_path.h"

OrbitPath::OrbitPath(Timer *timer) : BaseActor(timer)
{

}

#define SLICES 48

void OrbitPath::draw_me()
{
	GLfloat a = (apoapsis + periapsis) / 2.0f;
	GLfloat f = a - periapsis;
	GLfloat b = sqrt(pow(a, 2) - pow(f, 2));
	
	GLfloat xradius = a;
	GLfloat yradius = b;

	glRotatef(r_to_d(angle), 0, 0, 1.0f);
	glTranslatef(f, 0, 0);
	
	glColor3ub(192, 192, 0);

	glBegin(GL_LINE_LOOP);

	for (int t = 0; t <= SLICES; t++)
	{
		GLfloat theta = ((GLfloat)t / (GLfloat)SLICES) * 6.284;
		GLfloat x = xradius * cos(theta);
		GLfloat y = yradius * sin(theta);
		glVertex2f(x, y);
	}

	glEnd();
	
	glBegin(GL_POINTS);
	
	//glVertex2f(f, 0);
	glVertex2f(-f, 0);
	
	glEnd();
}
