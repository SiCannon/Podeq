#pragma once

#include <GL/freeglut.h>
#include "vector2f.h"

class Transform_Old
{
public:
	GLfloat scale;
	GLfloat translate_x;
	GLfloat translate_y;
	GLfloat rotation;
	void applyTRS();
	void applyST();
	Vector2f trans();
};
