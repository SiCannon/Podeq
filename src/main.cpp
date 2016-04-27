//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include "game_engine.h"
#include "gaf_glut.h"
#include <include/exit_on_escape.h>
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

//GameEngine *gameEngine;

Timer *timer;
Monster *monster;
Planet *planet;
Podeq::Ellipse *ellipse;
Ship *ship;
OrbitPath *orbit_path;
Orbit *orbit;

void calc();
GLfloat r_to_d(GLfloat r);

GLfloat r_angle;
void debug();
void debug_orbit_path(OrbitPath *path);

void display()
{
	timer->tick();

	//calc();
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//planet->draw();
	//ellipse->draw();
	orbit_path->draw();
	//ship->draw();
	

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
	textResetBottomLeft();
	debug_orbit_path(orbit_path);
	textReset(1);
	textOut("  shipx="); textOutFloat(ship->transform->translate_x);
	textOut("  shipy="); textOutFloat(ship->transform->translate_y);
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

/*void calc()
{
	GLfloat rs = distanceSquared(planet->transform, ship->transform);
	GLfloat a = GravConstant * planet->mass / rs;
	GLfloat t = angleTo(ship->transform, planet->transform);
	GLfloat ax = a * cos(t);
	GLfloat ay = a * sin(t);
	ship->accel(ax, ay);
}*/

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
	gameEngine = new GameEngine();
	gameEngine->register_inputTask(new ExitOnEscape());

	timer = new Timer();
	monster = new Monster(timer);
	planet = new Planet(timer, planet_mass);
	ellipse = new Podeq::Ellipse(timer);
	
	ship = new Ship(start_ship_vx, start_ship_vy, planet);
	ship->transform->translate_x = start_ship_x;
	ship->transform->translate_y = start_ship_y;
	
	gameEngine->register_drawTask(planet);
	gameEngine->register_drawTask(ship);
	gameEngine->register_updateTask(ship);

	orbit = new Orbit();
	
	orbit_path = new OrbitPath();
	calc_orbit();
	
	
	init_glut(argc, argv, "Podeq", display);

	delete(monster);
	delete(timer);

	delete(gameEngine);

	return EXIT_SUCCESS;
}
