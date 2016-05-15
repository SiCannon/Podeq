#include <math.h>
#include <GL/freeglut.h>
#include <include/gaf_math.h>
#include <include/textutils.h>
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
	if (orbit->is_hyperbolic())
	{
		return;
	}



	GLfloat a = (orbit->Ra + orbit->Rp) / 2.0f;
	GLfloat f = a - orbit->Rp;
	GLfloat b = sqrtf(powf(a, 2) - powf(f, 2));
	
	GLfloat xradius = a;
	GLfloat yradius = b;

	glRotatef(r_to_d(orbit->angle), 0, 0, 1.0f);
	glTranslatef(f, 0, 0);
	
	glColor3ub(64, 32, 0);

	glOpenEllipse(xradius, yradius, SLICES);
	
	glPushMatrix();
	glLoadIdentity();
	glColor3ub(192, 192, 192);
	textReset(1);
	textOut("e:");
	textOutFloat(orbit->e);
	textOut(", Rp:");
	textOutFloat(orbit->Rp);
	textOut(", Ra:");
	textOutFloat(orbit->Ra);
	textOut(", nu:");
	textOutFloat(orbit->nu);
	textOut(", angle:");
	glf angle_d = r_to_d(orbit->angle);
	while (angle_d >= 360.0f)
	{
		angle_d -= 360.0f;
	}
	while (angle_d < 0.0f)
	{
		angle_d += 360.0f;
	}
	textOutFloat(angle_d);
	glPopMatrix();

	//glBegin(GL_POINTS);
	
	//glVertex2f(f, 0);
	//glVertex2f(-f, 0);
	//glTranslatef(-f, 0, 0);
	//glSolidCircle(0.1f, 4);
	//glVertex2f(0, 0);
	
	//glEnd();
}
