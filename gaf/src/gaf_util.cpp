#include <GL/freeglut.h>

GLubyte *colorv(GLubyte r, GLubyte g, GLubyte b)
{
	GLubyte* c = (GLubyte*)malloc(3 * sizeof(GLubyte));
	c[0] = r;
	c[1] = g;
	c[2] = b;
	return c;
}