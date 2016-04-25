//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include "screenutil.h"
#include "keyboard.h"
#include "gaf_math.h"
#include "textutils.h"

#include "defines.h"
#include "base_actor.h"
#include "monster.h"
#include "planet.h"
#include "orbit_path.h"
#include "ellipse.h"
#include "ship.h"
#include "omech.h"
#include "start_params.h"
#include "orbit.h"

Timer *timer;
Monster *monster;
Planet *planet;
Podeq::Ellipse *ellipse;
Ship *ship;
OrbitPath *orbit_path;
OrbitPath *orbit_path2;
Orbit *orbit;

void handleInput();
void calc();
GLfloat r_to_d(GLfloat r);

GLfloat r_angle;
void debug();
void debug_orbit_path(OrbitPath *path);

void display()
{
	timer->tick();
	
	handleInput();
	calc();
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	planet->draw();
	//ellipse->draw();
	ship->draw();
	orbit_path->draw();
	//orbit_path2->draw();

	//monster->draw();

	glColor3ub(192, 192, 0);
	glBegin(GL_LINES);
	glVertex2f(start_ship_x, start_ship_y);
	glVertex2f(start_ship_x + start_ship_vx, start_ship_y + start_ship_vy);
	glEnd();

	textResetBottomLeft();
	/*textOut("nu=");
	textOutFloat(r_to_d(orbit->nu));
	textOut("  r_angle=");
	textOutFloat(r_to_d(r_angle));
	textOut("  arg=");
	textOutFloat(r_to_d(orbit_path->angle));
	textOut("  Ra=");
	textOutFloat(orbit->Ra);
	textOut("  Rp=");
	textOutFloat(orbit->Rp);*/
	debug();

	glutSwapBuffers();
	glutPostRedisplay();
}

void debug()
{
	debug_orbit_path(orbit_path);
	debug_orbit_path(orbit_path2);
}

void debug_orbit_path(OrbitPath *path)
{
	textOut("  arg=");
	textOutFloat(path->angle);
	textOut("  Ra=");
	textOutFloat(path->apoapsis);
	textOut("  Rp=");
	textOutFloat(path->periapsis);
}


GLfloat distanceSquared(Transform *t1, Transform *t2)
{
	return SQR(t1->translate_x - t2->translate_x) + SQR(t1->translate_y - t2->translate_y); 
}

GLfloat angleTo(Transform *me, Transform *target)
{
	GLfloat dx = (target->translate_x - me->translate_x);
	GLfloat dy = (target->translate_y - me->translate_y);
	if (dx == 0)
	{
		return dy > 0 ? PI_BY_2 : 3 * PI_BY_2;
	}
	else
	{
		GLfloat res = atan(dy / dx);
		if (dx < 0)
		{
			res += PI;
		}
		else if (dy < 0)
		{
			res += TWO_PI;
		}
		return res;
	}
}

void calc()
{
	GLfloat rs = distanceSquared(planet->transform, ship->transform);
	GLfloat a = GravConstant * planet->mass / rs;
	GLfloat t = angleTo(ship->transform, planet->transform);
	GLfloat ax = a * cos(t);
	GLfloat ay = a * sin(t);
	ship->accel(ax, ay);
}

void handleInput()
{
	if (keyState[27])
	{
		glutLeaveMainLoop();
	}
	
	GLfloat inc = 0.02f;
	if (keyState['a'])
	{
		ellipse->xradius += inc;
	}
	if (keyState['d'])
	{
		ellipse->xradius -= inc;
	}
	if (keyState['w'])
	{
		ellipse->yradius -= inc;
	}
	if (keyState['s'])
	{
		ellipse->yradius += inc;
	}
}

void calc_orbit()
{
	r_angle = angleBetween(1.0f, 0.0f, start_ship_x, start_ship_y);
	
	orbit->calc(planet_x, planet_y, start_ship_x, start_ship_y, start_ship_vx, start_ship_vy, planet->GM());
	orbit_path->apoapsis = orbit->Ra;
	orbit_path->periapsis = orbit->Rp;
	
	if (orbit->nu < 0)
	{
		orbit->nu += TWO_PI;
	}
	
	orbit_path->angle = r_angle - (orbit->nu - PI);
}

int main(int argc, char **argv)
{
	timer = new Timer();
	monster = new Monster(timer);
	planet = new Planet(timer, planet_mass);
	ellipse = new Podeq::Ellipse(timer);
	
	ship = new Ship(timer, start_ship_vx, start_ship_vy);
	ship->transform->translate_x = start_ship_x;
	ship->transform->translate_y = start_ship_y;
	
	orbit = new Orbit();
	
	orbit_path = new OrbitPath(timer);
	calc_orbit();
	
	orbit_path2 = new OrbitPath(timer);
	orbit_path2->apoapsis = 5.0f;
	orbit_path2->periapsis = 1.0f;
	orbit_path2->angle = PI_BY_8;
	
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(INTIAL_WNDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
	glutCreateWindow("Podeq");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutPassiveMotionFunc(saveMousePosition);
	//glutMotionFunc(saveMousePosition);
	//glutMouseFunc(processMouse);
	glutKeyboardFunc(getKeyboardDown);
	glutKeyboardUpFunc(getKeyboardUp);
	//glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();

	delete(monster);
	delete(timer);

	return EXIT_SUCCESS;
}
