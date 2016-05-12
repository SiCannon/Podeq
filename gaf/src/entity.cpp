#include "../include/entity.h"
#include "../include/polygon2f.h"
#include "../include/transform.h"

Entity::Entity(unsigned int vertex_mode, short vertex_count, short index_count)
{
	polygon = new Polygon2f(vertex_mode, vertex_count, index_count);
	transform = new Transform();
	transform->scale = 1.0f;
}