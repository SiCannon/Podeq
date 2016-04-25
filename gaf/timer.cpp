#include <GL/freeglut.h>
#include "timer.h"

void Timer::tick()
{
	int newTicks = glutGet(GLUT_ELAPSED_TIME);
	intervalTicks = newTicks - totalTicks;
	totalTicks = newTicks;
}

GLfloat Timer::intervalSeconds()
{
	return intervalTicks / 1000.0f;
}