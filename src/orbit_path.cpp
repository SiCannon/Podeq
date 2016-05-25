#include <math.h>
#include <GL/freeglut.h>
#include <include/gaf_math.h>
#include <include/textutils.h>
#include "orbit_path.h"
#include "include/shapes.h"
#include "include/vector2f.h"
#include "defines.h"

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

	//draw_future_ghost();

#ifdef draw_calculated_orbit
	draw_calculated_position();
#endif

	draw_stats();
}

void OrbitPath::draw_ellipse()
{
	glPushMatrix();

	glf a = (orbit->Ra + orbit->Rp) / 2.0f;
	glf f = a - orbit->Rp;
	glf b = sqrtf(powf(a, 2) - powf(f, 2));

	glf xradius = a;
	glf yradius = b;

	glRotatef(r_to_d(orbit->angle), 0, 0, 1.0f);
	glTranslatef(f, 0, 0);

	glColor3ub(64, 32, 0);

	glOpenEllipse(xradius, yradius, SLICES);

	glPopMatrix();
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

void OrbitPath::draw_calculated_position()
{
	auto p1 = orbit->position_p;
	auto p2 = p1 + orbit->position_v * 10.0f;

	glPushMatrix();

	glColor3ub(192, 192, 0);
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	
	glEnd();

	glPopMatrix();
}

void OrbitPath::draw_future_ghost()
{
/*	Vector2f v = orbit->position_at_time(1.0f);
	glColor3ub(0, 255, 0);
	
	glf size = 0.1f;
	glBegin(GL_LINES);

	glVertex2f(-size, 0);
	glVertex2f(+size, 0);
	glVertex2f(0, -size);
	glVertex2f(0, +size);


	glVertex2f(v.x - size, v.y);
	glVertex2f(v.x + size, v.y);
	glVertex2f(v.x, v.y - size);
	glVertex2f(v.x, v.y + size);
	glEnd();*/

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
	textOut(", position_speed:");
	textOutFloat(orbit->position_speed * 100.0f);
	textOut(", position_phi:");
	textOutFloat(r_to_d(orbit->position_phi));
	textOut(", position_theta:");
	textOutFloat(r_to_d(orbit->position_theta));
	textOut(", is_clockwise:");
	textOutInt(orbit->is_clockwise ? 1 : 0);
	glPopMatrix();
}

