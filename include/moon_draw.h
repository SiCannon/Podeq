#pragma once

#include <include/draw_task.h>

class Moon;

class MoonDraw : public DrawTask
{
public:
	MoonDraw(Moon *moon);
	void draw();
private:
	Moon *moon;
};