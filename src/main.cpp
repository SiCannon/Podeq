//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include <include/game_engine.h>
#include "gaf_glut.h"
#include <include/exit_on_escape.h>
#include "screenutil.h"
#include "keyboard.h"
#include "gaf_math.h"
#include "textutils.h"
#include "include/draw_task.h"

#include "defines.h"
#include <include/base_actor.h>
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

//void calc();
//GLfloat r_to_d(GLfloat r);

//GLfloat r_angle;
//void debug();
//void debug_orbit_path(OrbitPath *path);

/*void display()
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
	textOutFloat(orbit->Rp);* /
	debug();

	glutSwapBuffers();
	glutPostRedisplay();
}*/

/*void debug()
{
	textResetBottomLeft();
	debug_orbit_path(orbit_path);
	textReset(1);
	textOut("  shipx="); textOutFloat(ship->transform->translate_x);
	textOut("  shipy="); textOutFloat(ship->transform->translate_y);
}*/

/*void debug_orbit_path(OrbitPath *path)
{
	textOut("  arg=");
	textOutFloat(path->angle);
	textOut("  Ra=");
	textOutFloat(path->apoapsis);
	textOut("  Rp=");
	textOutFloat(path->periapsis);
}*/

class Test : public BaseActor, public InputTask, public UpdateTask
{
public:
	void draw_me()
	{
		/*
		glBegin(GL_TRIANGLES);

		glColor3ub(192, 192, 192);
		glVertex2i(0, 0);
		glVertex2i(1, 0);
		glVertex2i(0, 1);

		glEnd();
		*/
		glPushMatrix();
		glLoadIdentity();
		//textTopLeft();
		//textResetBottomLeft();
		//printText(false, rasterLeft, rasterBottom, "hello", 0, 192, 192);
		textPos(1);
		textYellow();
		//textOutFloat(orbit->);
		glPopMatrix();
	};
	void input(Keyboard *keyboard)
	{
		if (keyboard->keyState['w'])
		{
			gameEngine->world_transform->scale += 0.01f;
		}
		if (keyboard->keyState['s'])
		{
			gameEngine->world_transform->scale -= 0.01f;
		}
	};
	void update(Timer *timer)
	{

	};
};

int main(int argc, char **argv)
{
	gameEngine = new GameEngine();
	gameEngine->register_inputTask(new ExitOnEscape());

	timer = new Timer();
	monster = new Monster(timer);
	planet = new Planet(planet_mass);
	planet->transform->translate_x = planet_x;
	planet->transform->translate_y = planet_y;
	ellipse = new Podeq::Ellipse(timer);
	
	ship = new Ship(start_ship_vx, start_ship_vy, planet);
	ship->transform->translate_x = start_ship_x;
	ship->transform->translate_y = start_ship_y;
	
	orbit = new Orbit();
	orbit->calc(planet_x, planet_y, start_ship_x, start_ship_y, start_ship_vx, start_ship_vy, planet->GM());

	orbit_path = new OrbitPath(orbit);
	orbit_path->transform->translate_x = planet_x;
	orbit_path->transform->translate_y = planet_y;
	
	gameEngine->register_drawTask(planet);
	gameEngine->register_drawTask(ship);
	gameEngine->register_drawTask(orbit_path);

	gameEngine->register_updateTask(ship);

	Test *test = new Test();
	test->transform->translate_x = 2.0f;
	test->transform->translate_y = 2.0f;
	gameEngine->register_drawTask(test);
	gameEngine->register_inputTask(test);

	init_glut(argc, argv, "Podeq");

	
	

	delete(monster);
	delete(timer);

	delete(gameEngine);

	return EXIT_SUCCESS;
}
