#pragma once

#include <GL/freeglut.h>
#include "gaf.h"

struct Vector2f
{
	glf x, y;
};

Vector2f minus(Vector2f v1, Vector2f v2);
Vector2f swap_elements(Vector2f v);
Vector2f normal(Vector2f v);
Vector2f normal(Vector2f v1, Vector2f v2);
glf length(Vector2f v);
glf dot_product(Vector2f v1, Vector2f v2);