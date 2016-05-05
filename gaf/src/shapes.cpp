#include <math.h>
#include <GL/freeglut.h>
#include <include/shapes.h>

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

void glOpenEllipse(GLfloat xradius, GLfloat yradius, int slices)
{
	glBegin(GL_LINE_LOOP);

	for (int t = 0; t <= slices; t++)
	{
		GLfloat theta = ((GLfloat)t / (GLfloat)slices) * 6.284;
		GLfloat x = xradius * cos(theta);
		GLfloat y = yradius * sin(theta);
		glVertex2f(x, y);
	}

	glEnd();
}

void glIsoTriangle(GLfloat width, GLfloat height, GLfloat offsetFromBase)
{
	glBegin(GL_TRIANGLES);

	glVertex2f(-width / 2.0f, -offsetFromBase);
	glVertex2f(width / 2.0f, -offsetFromBase);
	glVertex2f(0, height - offsetFromBase);

	glEnd();
}

void glTorus(GLfloat innerRadius, GLfloat outerRadius, const GLubyte *innerColor, const GLubyte *outerColor, int slices)
{
	glBegin(GL_TRIANGLE_STRIP);

	GLfloat theta, x, y;
	GLfloat s = (GLfloat)slices;

	for (int t = 0; t <= slices; t++)
	{
		theta = ((GLfloat)t / s) * 6.284f;
		x = innerRadius * sin(theta);
		y = innerRadius * cos(theta);
		glColor3ubv(innerColor);
		glVertex2f(x, y);
		x = outerRadius * sin(theta);
		y = outerRadius * cos(theta);
		glColor3ubv(outerColor);
		glVertex2f(x, y);
	}

	glEnd();
}