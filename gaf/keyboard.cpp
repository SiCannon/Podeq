#include <GL/freeglut.h>
#include "game_engine.h"
#include "keyboard.h"
#include "transform.h"
#include "defines.h"

void getKeyboardDown(unsigned char key, int x, int y)
{
	gameEngine->keyboard->keyState[key] = true;
}

void getKeyboardUp(unsigned char key, int x, int y)
{
	gameEngine->keyboard->keyState[key] = false;
}
