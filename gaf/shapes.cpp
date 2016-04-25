#include <math.h>
#include <GL/freeglut.h>
#include "shapes.h"

void glSolidCircle(GLfloat radius, int slices)
{
    glSolidEllipse(radius, radius, slices);
}

void glSolidEllipse(GLfloat xradius, GLfloat yradius, int slices)
{
	glBegin(GL_TRIANGLE_FAN);
    
    glVertex2f(0, 0);
    
    for (int t = 0; t <= slices; t++)
    {
        GLfloat theta = ((GLfloat)t / (GLfloat)slices) * 6.284;
		GLfloat x = xradius * sin(theta);
		GLfloat y = yradius * cos(theta);
        glVertex2f(x, y);
    }
    
	glEnd();
}