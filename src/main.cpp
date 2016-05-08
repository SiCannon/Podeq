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

PodeqGame *podeq;

class Test : public BaseActor, public InputTask, public UpdateTask
{
public:
	void draw_me()
	{
		/*
		glPushMatrix();
		glLoadIdentity();
		textPos(1);
		textYellow();
		textOutFloat(123.456f);
		glPopMatrix();
		*/
	};
	void input(Keyboard *keyboard)
	{
		GLfloat scale_inc = 0.1f;
		if (keyboard->special[GLUT_KEY_PAGE_UP])
		{
			gameEngine->world_transform->scale *= scale_mult;
		}
		if (keyboard->special[GLUT_KEY_PAGE_DOWN])
		{
			gameEngine->world_transform->scale /= scale_mult;
		}
	};
	void update(Timer *timer)
	{
		gameEngine->world_transform->translate_x = -podeq->ship->transform->translate_x;
		gameEngine->world_transform->translate_y = -podeq->ship->transform->translate_y;
	};
};

int main(int argc, char **argv)
{
	gameEngine = new GameEngine();
	podeq = new PodeqGame();

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
