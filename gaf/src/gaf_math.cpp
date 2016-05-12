#include <math.h>
#include <GL/freeglut.h>
#include <include/gaf.h>
#include <include/gaf_math.h>
#include <include/transform_old.h>
#include <include/vector2f.h>

GLfloat angleBetween(GLfloat ux, GLfloat uy, GLfloat vx, GLfloat vy)
{
    GLfloat angle = atan2f(vy, vx) - atan2f(uy, ux);
    if (angle < 0)
    {
        angle += TWO_PI;
    }
    return angle;
}

GLfloat r_to_d(GLfloat r)
{
	return 360.0f * (r / TWO_PI);
}

GLfloat d_to_r(GLfloat r)
{
	return TWO_PI * (r / 360.0f);
}

GLfloat distanceSquared(Transform_Old *t1, Transform_Old *t2)
{
	return SQR(t1->translate_x - t2->translate_x) + SQR(t1->translate_y - t2->translate_y);
}

glf distanceSquared(Vector2f& v1, Vector2f& v2)
{
	return (v2 - v1).length_squared();
}

glf angleTo(Vector2f& me, Vector2f& target)
{
	Vector2f d = target - me;
	if (d.x == 0)
	{
		return d.y > 0 ? PI_BY_2 : 3 * PI_BY_2;
	}
	else
	{
		GLfloat res = atanf(d.y / d.x);
		if (d.x < 0)
		{
			res += PI;
		}
		else if (d.y < 0)
		{
			res += TWO_PI;
		}
		return res;
	}
}

GLfloat angleTo(Transform_Old *me, Transform_Old *target)
{
	GLfloat dx = (target->translate_x - me->translate_x);
	GLfloat dy = (target->translate_y - me->translate_y);
	if (dx == 0)
	{
		return dy > 0 ? PI_BY_2 : 3 * PI_BY_2;
	}
	else
	{
		GLfloat res = atanf(dy / dx);
		if (dx < 0)
		{
			res += PI;
		}
		else if (dy < 0)
		{
			res += TWO_PI;
		}
		return res;
	}
}
