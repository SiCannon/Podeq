#pragma once

#include <GL/freeglut.h>
#include <include/gaf.h>
#include <include/draw_task.h>

class Moon;

class MoonDraw : public DrawTask
{
public:
	MoonDraw(Moon *moon, glf radius, GLubyte red, GLubyte green, GLubyte blue);
	void draw();
private:
	Moon *moon;
	glf radius;
	GLubyte red;
	GLubyte green;
	GLubyte blue;
};