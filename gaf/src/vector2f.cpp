#include <math.h>
#include "../include/gaf_math.h"
#include "../include/gaf.h"
#include "../include/vector2f.h"

Vector2f swap_elements(Vector2f v)
{
	Vector2f result;
	result.x = v.y;
	result.y = v.x;
	return result;
}

Vector2f normal(Vector2f v1, Vector2f v2)
{
	return normal(v2 - v1);
}

Vector2f normal(Vector2f v)
{
	Vector2f d = swap_elements(v);
	d.y = -d.y;
	glf len = length(d);
	if (len > 0)
	{
		d.x /= len;
		d.y /= len;
	}
	return d;
}

glf length(Vector2f v)
{
	return sqrtf(SQR(v.x) + SQR(v.y));
}

glf dot_product(Vector2f v1, Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}