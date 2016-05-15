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
	if (orbit->is_hyperbolic())
	{
		draw_hyperbola();
	}
	else
	{
		draw_ellipse();
	}

	draw_stats();
}

void OrbitPath::draw_ellipse()
{
	glf a = (orbit->Ra + orbit->Rp) / 2.0f;
	glf f = a - orbit->Rp;
	glf b = sqrtf(powf(a, 2) - powf(f, 2));

	glf xradius = a;
	glf yradius = b;

	glRotatef(r_to_d(orbit->angle), 0, 0, 1.0f);
	glTranslatef(f, 0, 0);

	glColor3ub(64, 32, 0);

	glOpenEllipse(xradius, yradius, SLICES);
}

void OrbitPath::draw_hyperbola()
{
	glf e = orbit->e;
	glf a = orbit->Rp / (e - 1);

	glRotatef(r_to_d(orbit->angle + PI), 0, 0, 1.0f);
	glBegin(GL_LINE_STRIP);

	glColor3ub(48, 48, 0);

	glf theta = acosf(-1 / e);

	glf start_theta = -theta + 0.01f;
	glf end_theta = theta - 0.01f;

	for (glf t = start_theta; t < end_theta; t += 0.01f)
	{
		glf r = a * (SQR(e) - 1) / (1 + e * cosf(t));
		glf x = r * cosf(t);
		glf y = r * sinf(t);
		glVertex2f(x, y);
	}

	glEnd();

}

void OrbitPath::draw_stats()
{
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
	textOutFloat(r_to_d(orbit->nu));
	textOut(", angle:");
	textOutFloat(r_to_d(orbit->angle));
	glPopMatrix();
}

