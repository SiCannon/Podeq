#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include <include/game_engine.h>
#include "gaf_glut.h"
#include "screenutil.h"
#include <include/keyboard.h>
#include <include/gaf_math.h>
#include <include/textutils.h>
#include "include/draw_task.h"
#include "start_params.h"

#include "defines.h"
#include <include/base_actor.h>

#include "podeq_game.h"

#include <include/Polygon2f.h>
#include <include/Polygon2f_draw.h>

PodeqGame *podeq;

class Test : public BaseActor, public InputTask, public UpdateTask
{
public:
	void draw_me()
	{
	};
	void input(Keyboard *keyboard)
	{
	};
	void update(Timer *timer)
	{
	};
};

class Hex
{
public:
	Polygon2f *poly;
	Polygon2f_Draw *polydraw;
	Hex()
	{
		poly = new Polygon2f();
		poly->set_size(3);
		poly->set_vertex(0, -1.0f, 0);
		poly->set_vertex(1, 1.0f, 0);
		poly->set_vertex(2, 0, 2.0f);
		polydraw = new Polygon2f_Draw(poly);
		gameEngine->register_drawTask(polydraw);
	}
};

int main(int argc, char **argv)
{
	gameEngine = new GameEngine();
	podeq = new PodeqGame();
	//new Hex();
	gameEngine->world_transform->scale = start_scale;

	Test *test = new Test();
	test->transform->translate_x = 2.0f;
	test->transform->translate_y = 2.0f;
	gameEngine->register_drawTask(test);
	gameEngine->register_inputTask(test);
	gameEngine->register_updateTask(test);

	init_glut(argc, argv, "Podeq");

	delete(podeq);
	delete(gameEngine);

	return EXIT_SUCCESS;
}
