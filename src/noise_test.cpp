#include <GL/freeglut.h>
#include "../include/noise_test.h"
#include <include/textutils.h>
#include <limits.h>

GLfloat n(int x, GLfloat max)
{
	switch (x)
	{
		case 1: return 1;
		case 2: return -2;
		case 3: return -1;
		case 4: return 3;
		default: return 0;
	}
}

int fast_hash(unsigned long a)
{
	a = (a ^ 61) ^ (a >> 16);
	a = a + (a << 3);
	a = a ^ (a >> 4);
	a = a * 0x27d4eb2d;
	a = a ^ (a >> 15);
	return a;
}

GLfloat nr(unsigned long x, GLfloat max)
{
	unsigned long r = fast_hash(x);
	return ((GLfloat)r / (GLfloat)(ULONG_MAX)) * max - (max / 2.0f);
}

GLfloat lerp(GLfloat a, GLfloat b, GLfloat x)
{
	return a * (1.0f - x) + b * x;
}

GLfloat hermite(GLfloat x)
{
	return (x * x) * (3.0f - 2.0f * x);
}

GLfloat quint(GLfloat x)
{
	return (x * x * x) * (6.0f * x * x - 15.0f * x + 10.0f);
}

NoiseTest::NoiseTest()
{
	slices = 4.0f;
	x_offset = -10.0f;
}

void NoiseTest::draw()
{
	glLoadIdentity();
	
	glBegin(GL_LINES);
	glColor3ub(64, 64, 64);
	glVertex2i(0, 10);
	glVertex2i(0, -10);
	glVertex2i(-10, 0);
	glVertex2i(10, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);

	glColor3ub(255, 255, 255);

	int islices = slices;
	GLfloat slice = 1.0f / (GLfloat)islices;

	for (int i = -20; i < 20; i++)
	{
		int ii = i + (int)x_offset;
		GLfloat a = nr(ii, 20);
		GLfloat b = nr(ii + 1, 20);
		for (int j = 0; j < islices; j++)
		{
			GLfloat dx = j * slice;
			GLfloat x = (GLfloat)i + dx;
			GLfloat y = lerp(a, b, quint(dx));
			glVertex2f(x, y);
		}
	}

	glEnd();

	textReset(1);
	textOutFloat(slices);
	textReset(2);
	textOutInt(islices);
}

void NoiseTest::input(Keyboard * keyboard)
{
	GLfloat sliceinc = 0.1f;

	if (keyboard->keyState['p'])
	{
		slices += sliceinc;
	}
	if (keyboard->keyState['l'])
	{
		slices -= sliceinc;
	}
	if (keyboard->keyState['i'])
	{
		x_offset -= sliceinc;
	}
	if (keyboard->keyState['o'])
	{
		x_offset += sliceinc;
	}
}
