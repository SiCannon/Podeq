#include <GL/freeglut.h>
#include "../include/page_to_zoom.h"
#include "../include/keyboard.h"
#include "../include/game_engine.h"

PageToZoom::PageToZoom(GLfloat scale_mult)
{
	this->scale_mult = scale_mult;
}

void PageToZoom::input(Keyboard *keyboard)
{
	if (keyboard->special[GLUT_KEY_PAGE_UP])
	{
		gameEngine->world_transform->scale *= scale_mult;
	}
	if (keyboard->special[GLUT_KEY_PAGE_DOWN])
	{
		gameEngine->world_transform->scale /= scale_mult;
	}
}