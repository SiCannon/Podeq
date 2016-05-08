#include <math.h>
#include <GL/freeglut.h>
#include <include/gaf_math.h>
#include "orbit_path.h"
#include "include/shapes.h"

OrbitPath::OrbitPath(Orbit *orbit) : BaseActor()
{
	this->orbit = orbit;
}

#define SLICES 192

void OrbitPath::draw_me()
{
	//apoapsis = orbit->Ra;
	//periapsis = orbit->Rp;


	GLfloat a = (orbit->Ra + orbit->Rp) / 2.0f;
	GLfloat f = a - orbit->Rp;
	GLfloat b = sqrt(pow(a, 2) - pow(f, 2));
	
	GLfloat xradius = a;
	GLfloat yradius = b;

	glRotatef(r_to_d(orbit->angle), 0, 0, 1.0f);
	glTranslatef(f, 0, 0);
	
	glColor3ub(64, 32, 0);

	glOpenEllipse(xradius, yradius, SLICES);
	
	//glBegin(GL_POINTS);
	
	//glVertex2f(f, 0);
	//glVertex2f(-f, 0);
	//glTranslatef(-f, 0, 0);
	//glSolidCircle(0.1f, 4);
	//glVertex2f(0, 0);
	
	//glEnd();
}
