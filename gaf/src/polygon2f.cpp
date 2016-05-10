#include "../include/vector2f.h"
#include "../include/polygon2f.h"

Polygon2f::Polygon2f(unsigned int vertex_mode, short vertex_count, short index_count)
{
	this->vertex_mode = vertex_mode;
	set_size(vertex_count, index_count);

	color = NULL;
}

void Polygon2f::set_size(short vertex_count, short index_count)
{
	this->vertex_count = vertex_count;
	vertices = (Vector2f*)malloc(vertex_count * sizeof(Vector2f));

	this->index_count = index_count;
	indices = (short*)malloc(index_count * sizeof(short));
}

void Polygon2f::set_vertex(short number, GLfloat x, GLfloat y)
{
	Vector2f v = { x, y };
	set_vertex(number, v);
}

void Polygon2f::set_vertex(short number, Vector2f v)
{
	vertices[number] = v;
}

void Polygon2f::set_index(short number, short index)
{
	indices[number] = index;
}

Vector2f Polygon2f::get_edge(short number)
{
	short v1 = number;
	short v2 = number + 1;
	if (v2 >= vertex_count)
	{
		v2 = 0;
	}
	return minus(vertices[v2], vertices[v1]);
}
