#pragma once

#include <GL/freeglut.h>
#include "input_task.h"

class PageToZoom : public InputTask
{
public:
	PageToZoom(GLfloat scale_mult);
	void input(Keyboard *keyboard);
private:
	GLfloat scale_mult;
};