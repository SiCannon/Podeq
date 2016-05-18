#pragma once

#include <GL/freeglut.h>
#include "gaf_math.h"
#include "gaf.h"

struct Vector2f
{
	glf x, y;
	Vector2f operator + (const Vector2f& v)
	{
		return { x + v.x, y + v.y };
	};
	Vector2f operator - (const Vector2f& v)
	{
		return { x - v.x, y - v.y };
	};
	Vector2f operator * (glf k)
	{
		return{ x * k, y * k };
	};
	glf length_squared()
	{
		return SQR(x) + SQR(y);
	};
	glf length()
	{
		return sqrtf(length_squared());
	};
	static Vector2f from_polar(GLfloat r, GLfloat theta)
	{
		return { r * cosf(theta), r * sinf(theta) };
	}
};

Vector2f swap_elements(Vector2f v);
Vector2f normal(Vector2f v);
Vector2f normal(Vector2f v1, Vector2f v2);
glf length(Vector2f v);
glf dot_product(Vector2f v1, Vector2f v2);