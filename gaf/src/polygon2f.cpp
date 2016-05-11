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
	transformed = (Vector2f*)malloc(vertex_count * sizeof(Vector2f));

	this->index_count = index_count;
	indices = (short*)malloc(index_count * sizeof(short));
}

void Polygon2f::set_vertex(short number, GLfloat x, GLfloat y)
{
	vertices[number].x = x;
	vertices[number].y = y;
	transformed[number] = transform(number);
}

void Polygon2f::set_vertex(short number, const Vector2f& v)
{
	vertices[number] = v;
	transformed[number] = transform(number);
}

void Polygon2f::set_index(short number, short index)
{
	indices[number] = index;
}

void Polygon2f::set_position(glf x, glf y)
{
	position.x = x;
	position.y = y;
	recalc_transformed();
}

void Polygon2f::set_position(const Vector2f& v)
{
	position.x = v.x;
	position.y = v.y;
	recalc_transformed();
}

void Polygon2f::add_position(const Vector2f& v)
{
	set_position(position + v);
}

Vector2f Polygon2f::transform(short number)
{
	return vertices[number] + position;
}

void Polygon2f::recalc_transformed()
{
	for (int i = 0; i < vertex_count; i++)
	{
		transformed[i] = transform(i);
	}
}

/*Vector2f Polygon2f::get_edge(short number)
{
	short v1 = number;
	short v2 = number + 1;
	if (v2 >= vertex_count)
	{
		v2 = 0;
	}
	return minus(vertices[v2], vertices[v1]);
}*/
