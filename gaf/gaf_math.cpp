#include <math.h>
#include <GL/freeglut.h>
#include "gaf_math.h" 

GLfloat angleBetween(GLfloat ux, GLfloat uy, GLfloat vx, GLfloat vy)
{
    GLfloat angle = atan2(vy, vx) - atan2(uy, ux);
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
