#include <math.h>
#include "gaf_math.h"
#include "orbit.h"
#include "omech.h"

Orbit::Orbit()
{
    
}

void Orbit::calc(GLfloat rx, GLfloat ry, GLfloat vx, GLfloat vy, GLfloat GM)
{
	GLfloat r = sqrt(SQR(rx) + SQR(ry));
	GLfloat vsq = SQR(vx) + SQR(vy);
	GLfloat phi = PI_BY_2 - angleBetween(rx, ry, vx, vy);
	
	GLfloat e = calc_e(r, vsq, GM, phi);
	GLfloat a = calc_a(r, vsq, GM);
	Rp = calc_Rp(a, e);
	Ra = calc_Ra(a, e);
	nu = calc_nu(r, vsq, GM, phi);
    angle = 0;
}

void Orbit::calc(GLfloat planet_x, GLfloat planet_y, GLfloat ship_x, GLfloat ship_y, GLfloat vx, GLfloat vy, GLfloat GM)
{
    GLfloat rx = ship_x - planet_x;
    GLfloat ry = ship_y - planet_y;
    calc(rx, ry, vx, vy, GM);
}