#pragma once

#include <GL/freeglut.h>

void glSolidCircle(GLfloat radius, int slices);
void glSolidEllipse(GLfloat xradius, GLfloat yradius, int slices);
void glOpenEllipse(GLfloat xradius, GLfloat yradius, int slices);
void glIsoTriangle(GLfloat width, GLfloat height, GLfloat offsetFromBase);
void glTorus(GLfloat innerRadius, GLfloat outerRadius, const GLubyte *innerColor, const GLubyte *outerColor, int slices);