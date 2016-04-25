#include <GL/freeglut.h>
#include "timer.h"

Timer::Timer()
{
	started = false;
}

void Timer::tick()
{
	int newTicks = glutGet(GLUT_ELAPSED_TIME);
	if (started)
	{
		intervalTicks = newTicks - totalTicks;
	}
	else
	{
		started = true;
		intervalTicks = 0;
	}
	totalTicks = newTicks;
}

GLfloat Timer::intervalSeconds()
{
	return intervalTicks / 1000.0f;
}