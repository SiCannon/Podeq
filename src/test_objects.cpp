#include <GL/freeglut.h>
#include "../include/test_objects.h"
#include "../include/orbit.h"
#include <include/gaf_util.h>
#include <include/vector2f.h>
#include <include/textutils.h>
#include <include/sat_collider.h>
#include <include/transform_old.h>
#include "planet.h"
#include "defines.h"

Hex::Hex()
{
	poly = new Polygon2f(GL_TRIANGLE_STRIP, 6, 6);
	
	poly->set_vertex(0, 0, 2.0f);
	poly->set_vertex(1, -1.0f, 1.0f);
	poly->set_vertex(2, -1.0f, -1.0f);
	poly->set_vertex(3, 0, -2.0f);
	poly->set_vertex(4, 1.0f, -1.0f);
	poly->set_vertex(5, 1.0f, 1.0f);

	poly->set_index(0, 0);
	poly->set_index(1, 1);
	poly->set_index(2, 5);
	poly->set_index(3, 2);
	poly->set_index(4, 4);
	poly->set_index(5, 3);

	poly->color = colorv(192, 192, 64);

	polydraw = new Polygon2f_Draw(poly);
}

Tri::Tri()
{
	poly = new Polygon2f(GL_TRIANGLES, 3, 3);

	poly->set_vertex(0, 5.0f, 0);
	poly->set_vertex(1, 7.0f, 0);
	poly->set_vertex(2, 6.0f, 2.0f);

	poly->set_index(0, 0);
	poly->set_index(1, 1);
	poly->set_index(2, 2);

	poly->color = colorv(192, 64, 192);

	polydraw = new Polygon2f_Draw(poly);
}

CollisionDetector::CollisionDetector(Hex * hex, Tri * tri)
{
	this->hex = hex;
	this->tri = tri;
}

void CollisionDetector::draw()
{
	textReset(2);
	glColor3ub(0, 64, 255);
	if (is_collision)
	{
		textOut("collision!");
	}
	else
	{
		textOut("...");
	}

}

void CollisionDetector::input(Keyboard *keyboard)
{
	glf incamount = 0.02f;

	glf xinc = 0;
	glf yinc = 0;
	Vector2f v = { 0, 0 };

	if (keyboard->keyState['a'])
	{
		v.x = -incamount;
	}
	if (keyboard->keyState['d'])
	{
		v.x = +incamount;
	}
	if (keyboard->keyState['w'])
	{
		v.y = +incamount;
	}
	if (keyboard->keyState['s'])
	{
		v.y = -incamount;
	}
	

	tri->poly->add_position(v);

	/*for (int i = 0; i < tri->poly->vertex_count; i++)
	{
		tri->poly->vertices[i].x += xinc;
		tri->poly->vertices[i].y += yinc;
	}*/
}

void CollisionDetector::update(Timer * timer)
{
	/*
	bool collision = true;

	for (short i = 0; i < hex->poly->vertex_count; i++)
	{
		short i1 = i;
		short i2 = i + 1;
		if (i2 >= hex->poly->vertex_count)
		{
			i2 = 0;
		}

		Vector2f a = hex->poly->vertices[i1];
		Vector2f b = hex->poly->vertices[i2];
		Vector2f n = normal(a, b);

		bool all_negative = true;

		for (short j = 0; j < tri->poly->vertex_count; j++)
		{
			glf dot = dot_product(minus(a, tri->poly->vertices[j]), n);
			if (dot >= 0)
			{
				all_negative = false;
				break;
			}
		}

		if (all_negative)
		{
			collision = false;
			break;
		}
	}
	is_collision = collision;
	*/

	SatCollider *collider = new SatCollider();
	is_collision = collider->collide(hex->poly, tri->poly);

	if (is_collision)
	{
		tri->poly->color[0] = 0;
	}
	else
	{
		tri->poly->color[0] = 255;
	}
}

Hyperbola::Hyperbola(Orbit *orbit)
{
	this->orbit = orbit;
	e = 1.1f;
}

void Hyperbola::update(Timer *timer)
{
	if ((orbit->e - 1) <= 0)
	{
		return;
	}

	e = orbit->e;
	a = orbit->Rp / (e - 1);
}

void Hyperbola::input(Keyboard *keyboard)
{
	glf e_inc = 0.01f;
	if (keyboard->keyState['.'])
	{
		e += e_inc;
	}
	if (keyboard->keyState[','])
	{
		e -= e_inc;
	}
}

void Hyperbola::draw()
{
	if (!orbit->is_hyperbolic())
	{
		return;
	}

	//glf e = 1.50f;
	//glf a = 1.0f;

	glPushMatrix();
	//glLoadIdentity();
	glRotatef(r_to_d(orbit->angle + PI), 0, 0, 1);
	glBegin(GL_LINE_STRIP);

	glColor3ub(192, 32, 192);

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

	glPopMatrix();


	glPushMatrix();
	glLoadIdentity();
	glColor3ub(192, 192, 32);
	textReset(2);
	textOut("e:");
	textOutFloat(e);
	textOut(", a:");
	textOutFloat(a);
	textOut(", angle:");
	textOutFloat(r_to_d(orbit->angle));
	glPopMatrix();

}

OrbitPredictor::OrbitPredictor(Orbit *orbit, Planet *planet)
{
	this->orbit = orbit;
	this->planet = planet;
}

void OrbitPredictor::draw()
{
#ifndef show_predicted_orbit
	return;
#endif
	//auto orbit = this->orbit;
	//auto planet = this->planet;

	auto draw = [this](glf g) -> void {
		Vector2f v = orbit->position_at_time(g);

		glPushMatrix();

		glTranslatef(planet->transform->translate_x + v.x, planet->transform->translate_y + v.y, 0);

		glf size = 0.05f;
		glBegin(GL_LINES);
		glVertex2f(-size, 0);
		glVertex2f(+size, 0);
		glVertex2f(0, -size);
		glVertex2f(0, +size);
		glEnd();

		glPopMatrix();
	};

	
	glf min = 10.0f;
	glf inc = 10.0f;
	glf max = 100.0f;

	for (glf g = min; g <= max; g += inc)
	{
		//draw(g);
	}

	draw(0);

}