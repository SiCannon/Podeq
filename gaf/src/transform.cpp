#include <GL/freeglut.h>
#include "../include/transform.h"

void Transform::applyTRS()
{
	glTranslatef(trans.x, trans.y, 0);
	glRotatef(rot, 0, 0, 1.0f);
	glScalef(scale, scale, scale);
}

void Transform::applyTR()
{
	glTranslatef(trans.x, trans.y, 0);
	glRotatef(rot, 0, 0, 1.0f);
}

void Transform::applyST()
{
	glScalef(scale, scale, scale);
	glTranslatef(trans.x, trans.y, 0);
}
