#include <GL/freeglut.h>
#include "../include/polygon2f_draw.h"
#include "../include/polygon2f.h"

Polygon2f_Draw::Polygon2f_Draw(Polygon2f *polygon)
{
	this->polygon = polygon;
}

void Polygon2f_Draw::draw()
{
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 255, 255);

	for (short i = 0; i < polygon->vertex_count; i++)
	{
		glVertex2f(polygon->vertices[i].x, polygon->vertices[i].y);
	}

	glEnd();
}
