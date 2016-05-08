#pragma once

#include "vector2f.h"

class Polygon2f
{
public:
	short vertex_count;
	Vector2f *vertices;
	short *indices;
	void set_size(short vertex_count);
	void set_vertex(short index, GLfloat x, GLfloat y);
	void set_vertex(short index, Vector2f v);
};