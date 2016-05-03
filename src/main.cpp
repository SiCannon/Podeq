#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include <include/game_engine.h>
#include "gaf_glut.h"
#include "screenutil.h"
#include "keyboard.h"
#include "gaf_math.h"
#include "textutils.h"
#include "include/draw_task.h"

#include "defines.h"
#include <include/base_actor.h>

#include "podeq_game.h"

PodeqGame *podeq;

class Test : public BaseActor, public InputTask, public UpdateTask
{
public:
	void draw_me()
	{
		glPushMatrix();
		glLoadIdentity();
		textPos(1);
		textYellow();
		textOutFloat(123.456);
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
	podeq = new PodeqGame();

	Test *test = new Test();
	test->transform->translate_x = 2.0f;
	test->transform->translate_y = 2.0f;
	gameEngine->register_drawTask(test);
	gameEngine->register_inputTask(test);

	init_glut(argc, argv, "Podeq");

	delete(podeq);
	delete(gameEngine);

	return EXIT_SUCCESS;
}
