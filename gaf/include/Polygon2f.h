#pragma once

#include "gaf.h"
#include "vector2f.h"

class Polygon2f
{
public:
	short vertex_count;
	Vector2f *vertices;
	Vector2f *transformed;
	short index_count;
	short *indices;
	GLubyte *color;
	Vector2f position;

	unsigned int vertex_mode;
	

	Polygon2f(unsigned int vertex_mode, short vertex_count, short index_count);
	
	void set_vertex(short number, GLfloat x, GLfloat y);
	void set_vertex(short number, const Vector2f& v);
	void set_index(short number, short index);
	void set_position(glf x, glf y);
	void set_position(const Vector2f& v);
	void add_position(const Vector2f& v);
	//Vector2f get_edge(short number);

private:
	
	void set_size(short vertex_count, short index_count);
	Vector2f transform(short number);
	void recalc_transformed();
};