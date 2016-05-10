#include <GL/freeglut.h>
#include "../include/polygon2f_draw.h"
#include "../include/polygon2f.h"
#include "../include/vector2f.h"

Polygon2f_Draw::Polygon2f_Draw(Polygon2f *polygon)
{
	this->polygon = polygon;
}

void Polygon2f_Draw::draw_me()
{
	glBegin(polygon->vertex_mode);

	if (polygon->color != NULL)
	{
		glColor3ubv(polygon->color);
	}

	for (short i = 0; i < polygon->index_count; i++)
	{
		short idx = polygon->indices[i];
		Vector2f v = polygon->vertices[idx];
		glVertex2f(v.x, v.y);
	}

	glEnd();
}
