#include "../include/vector2f.h"
#include "../include/polygon2f.h"

Polygon2f::Polygon2f()
{
	vertices = NULL;
	indices = NULL;
	color = NULL;
}

void Polygon2f::set_size(short vertex_count)
{
	this->vertex_count = vertex_count;
	vertices = (Vector2f*)malloc(vertex_count * sizeof(Vector2f));
}

void Polygon2f::set_vertex(short index, GLfloat x, GLfloat y)
{
	Vector2f v = { x, y };
	set_vertex(index, v);
}

void Polygon2f::set_vertex(short index, Vector2f v)
{
	vertices[index] = v;
}
