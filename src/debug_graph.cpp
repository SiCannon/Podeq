#include <GL/freeglut.h>
#include "debug_graph.h"
#include <include/screenutil.h>
#include "omech.h"
#include <include/gaf_math.h>

void draw_graph(double(*func)(double), GLubyte red, GLubyte green, GLubyte blue);

double square(double x)
{
	return x * x;
}

double true_to_ecc(double x)
{
	return TrueToEccenAnomalyf(0.71f, x);
}

double t_to_e_AstronomyAnswers(double nu)
{
	double e = 2.0;
	if (e < 1.0)
	{
		return 2.0 * atan(tan(nu / 2.0) / sqrt((1.0 + e) / (1.0 - e)));
	}
	else if (e == 1.0)
	{
		return 0;
	}
	else
	{
		return 2.0 * atanh(tan(nu / 2.0) / sqrt((e + 1.0) / (e - 1.0)));
	}
}

double min_x = -TWO_PI_d;
double max_x = TWO_PI_d;
double x_inc = 0.01;

double calc_max_y = false;
double min_y = -10.0;
double max_y = 10.0;

void draw_all()
{
	//draw_graph(true_to_ecc, 64, 192, 62);
	draw_graph(t_to_e_AstronomyAnswers, 192, 64, 62);
	
}

void DebugGraph::draw()
{
	glPushMatrix();
	glLoadIdentity();

	double asp = (double)aspect_ratio;
	double orth = (double)orthoSize;

	double x_size = max_x - min_x;
	double y_size;
	if (calc_max_y)
	{
		y_size = x_size / asp;
		max_y = min_y + y_size;
	}
	else
	{
		y_size = max_y - min_y;
	}

	double x_orth_size = 2.0 * orth * asp;
	double y_orth_size = 2.0 * orth;

	glScaled(x_orth_size / x_size, y_orth_size / y_size, 1);
	glTranslated(-(max_x + min_x) / 2.0, -(max_y + min_y) / 2.0, 0);


	glBegin(GL_LINES);
	glColor3ub(192, 192, 192);
	glVertex2f(min_x, 0);
	glVertex2f(max_x, 0);
	glVertex2f(0, min_y);
	glVertex2f(0, max_y);
	glEnd();

	draw_all();
	

	glPopMatrix();
}

void draw_graph(double(*func)(double), GLubyte red, GLubyte green, GLubyte blue)
{
	glBegin(GL_LINE_STRIP);
	glColor3ub(red, green, blue);

	glVertex2f(min_x, func(min_x));

	for (double x = min_x; x <= max_x; x += x_inc)
	{
		glVertex2f(x, func(x));
	}

	glEnd();
}

