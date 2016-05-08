#include <GL/freeglut.h>
#include "../include/noise_test.h"
#include <include/textutils.h>
#include <limits.h>
#include <include/gaf.h>
#include <math.h>

glf n(int x, glf max)
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

unsigned long fash_1(unsigned long a)
{
	a = (a ^ 61) ^ (a >> 16);
	a = a + (a << 3);
	a = a ^ (a >> 4);
	a = a * 0x27d4eb2d;
	a = a ^ (a >> 15);
	return a;
}

unsigned long fash_n(unsigned long a, unsigned int k)
{
	return fash_1(a + (2 << k));
}

// this does not work...
/*unsigned long fash_2(unsigned long x)
{
	x = (x << 13UL) ^ x;
	return (1.0 - ((x * (x * x * 15731UL + 789221UL) + 1376312589UL) & 0x7fffffff) / 1073741824.0);
}*/

glf noise_1(unsigned long x, unsigned int k)
{
	unsigned long r = fash_n(x, k);
	return (glf)r / (glf)(ULONG_MAX);
}

/*
double IntegerNoise(int n)
{
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

glf noise_2(int n, int p1, int p2, int p3)
{
	n = (2<<20) + n;
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return ((glf)nn / 2147483648.0f);
}

glf noise_2_1(int n)
{
	return noise_2(n, 60493, 19990303, 1376312589);
}
*/

glf noise(glf x, unsigned int k)
{
	return noise_1((unsigned long)x, k);
}

glf lerp(glf a, glf b, glf x)
{
	return a * (1.0f - x) + b * x;
}

glf hermite(glf x)
{
	return (x * x) * (3.0f - 2.0f * x);
}

glf quint(glf x)
{
	return (x * x * x) * (6.0f * x * x - 15.0f * x + 10.0f);
}

glf floork(glf x, glf q)
{
	return floorf(x / q) * q;
}

glf ceilk(glf x, glf q)
{
	return ceilf(x / q) * q;
}

glf part(glf x, glf fq, glf am, unsigned int k)
{
	glf xa = floork(x, fq);
	glf xb = ceilk(x, fq);
	glf a = noise(xa, k);
	glf b = noise(xb, k);
	glf d = (x - xa) / fq;
	return lerp(a, b, quint(d)) * am;
}

NoiseTest::NoiseTest()
{
	slices = 8.0f;
	x_offset = 0.0f;
}

void drawOne(glf sector_size, glf sector_height, glf slice, glf x_offset, glf fq, glf am)
{
	glBegin(GL_LINE_STRIP);
	for (glf x = 0; x < sector_size; x += slice)
	{
		glf xx = x + x_offset;
		glf y = part(xx, fq, am, 4);
		glVertex2f(x, y * sector_height);
	}
	glEnd();
}

void NoiseTest::draw()
{
	glLoadIdentity();
	glScalef(0.4f, 0.4f, 1.0f);
	glTranslatef(-20, -10, 0);
	
	glBegin(GL_LINES);
	glColor3ub(64, 64, 64);
	glVertex2i(0, 10);
	glVertex2i(0, -10);
	glVertex2i(-10, 0);
	glVertex2i(10, 0);
	glEnd();

	glf
		sector_size = 50.0f,
		sector_height = 20.0f,
		fq_0 = 16.0f,
		fq_1 = 8.0f,
		fq_2 = 4.0f,
		fq_3 = 2.0f,
		fq_4 = 1.0f,
		am_0 = 1.0f,
		am_1 = 0.5f,
		am_2 = 0.25f,
		am_3 = 0.125f,
		am_4 = 0.0625f;
	
	glf slice = 1.0f / slices;

	glColor3ub(255, 255, 0);
	
	glBegin(GL_LINE_STRIP);
	for (glf x = 0; x < sector_size; x += slice)
	{
		glf xx = x + x_offset;
		glf y =
			part(xx, fq_0, am_0, 1) +
			part(xx, fq_1, am_1, 4) +
			part(xx, fq_2, am_2, 10) +
			part(xx, fq_3, am_3, 20) +
			part(xx, fq_4, am_4, 28)
			;
		glVertex2f(x, y * sector_height);
	}
	glEnd();



	/*glColor3ub(255, 255, 0);
	drawOne(sector_size, sector_height, slice, x_offset, fq_1, am_1);
	glColor3ub(255, 0, 255);
	drawOne(sector_size, sector_height, slice, x_offset, fq_2, am_1);
	glColor3ub(0, 0, 255);
	drawOne(sector_size, sector_height, slice, x_offset, fq_3, am_1);
	*/

	/*textReset(1);
	textOutFloat(slices);
	textReset(2);
	textOutInt(islices);*/
}

void NoiseTest::input(Keyboard * keyboard)
{
	glf sliceinc = 0.1f;
	glf offsinc = 0.5f;

	if (keyboard->keyState['p'])
	{
		slices += sliceinc;
	}
	if (keyboard->keyState['l'])
	{
		slices -= sliceinc;
		if (slices < 1)
		{
			slices = 1;
		}
	}
	if (keyboard->keyState['i'])
	{
		x_offset -= offsinc;
	}
	if (keyboard->keyState['o'])
	{
		x_offset += offsinc;
	}
}
