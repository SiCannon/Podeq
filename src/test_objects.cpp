#include <GL/freeglut.h>
#include "../include/test_objects.h"
#include <include/gaf_util.h>
#include <include/vector2f.h>
#include <include/textutils.h>
#include <include/sat_collider.h>

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
	
	if (keyboard->keyState['a'])
	{
		xinc = -incamount;
	}
	if (keyboard->keyState['d'])
	{
		xinc = +incamount;
	}
	if (keyboard->keyState['w'])
	{
		yinc = +incamount;
	}
	if (keyboard->keyState['s'])
	{
		yinc = -incamount;
	}

	for (int i = 0; i < tri->poly->vertex_count; i++)
	{
		tri->poly->vertices[i].x += xinc;
		tri->poly->vertices[i].y += yinc;
	}
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
