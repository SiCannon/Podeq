#pragma once

#include "polygon2f.h"
#include "transform.h"

class Entity
{
public:
	Polygon2f *polygon;
	Transform *transform;
	Entity(unsigned int vertex_mode, short vertex_count, short index_count);
};