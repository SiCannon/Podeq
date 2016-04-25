#include <stdio.h>
#include <GL/freeglut.h>
#include "gaf_math.h"
#include "start_params.h"
#include "omech.h"
#include "orbit.h"
#include "defines.h"

int main()
{
    Orbit *orbit = new Orbit();
    orbit->calc(planet_x, planet_y, start_ship_x, start_ship_y, start_ship_vx, start_ship_vy, planet_mass * GravConstant);
    
    printf("nu = %f\n", orbit->nu);
    
    GLfloat angle = angleBetween(1.0f, 0.0f, 0.0f, 3.0f);
    angle = 360.0f * angle / TWO_PI;
    printf("angle = %f\n", angle);
    
    return 0;
}