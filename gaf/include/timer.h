#pragma once

#include <GL/freeglut.h>

class Timer
{
public:
	Timer();
	long totalTicks;
	long intervalTicks;
	void tick();
	GLfloat intervalSeconds();
	GLfloat totalSeconds();
private:
	bool started;
};
