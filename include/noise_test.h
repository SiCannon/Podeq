#pragma once

#include <include/draw_task.h>
#include <include/input_task.h>
#include <include/keyboard.h>

class NoiseTest : public DrawTask, public InputTask
{
private:
	GLfloat slices;
	GLfloat x_offset;
public:
	NoiseTest();
	void draw();
	void input(Keyboard *keyboard);
};