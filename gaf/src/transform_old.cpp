#include <GL/freeglut.h>
#include <include/transform_old.h>
#include <include/vector2f.h>

void Transform_Old::applyTRS()
{
	glTranslatef(translate_x, translate_y, 0);
	glRotatef(rotation, 0, 0, 1.0f);
	glScalef(scale, scale, scale);
}

void Transform_Old::applyST()
{
	glScalef(scale, scale, scale);
	glTranslatef(translate_x, translate_y, 0);
}

Vector2f Transform_Old::trans()
{
	return{ translate_x, translate_y };
}
