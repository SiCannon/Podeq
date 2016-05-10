#pragma once

#include "vector2f.h"

class Polygon2f
{
public:
	short vertex_count;
	Vector2f *vertices;
	short index_count;
	short *indices;
	GLubyte *color;
	unsigned int vertex_mode;

	Polygon2f(unsigned int vertex_mode, short vertex_count, short index_count);
	
	void set_vertex(short number, GLfloat x, GLfloat y);
	void set_vertex(short number, Vector2f v);
	void set_index(short number, short index);

	Vector2f get_edge(short number);

private:
	void set_size(short vertex_count, short index_count);
};