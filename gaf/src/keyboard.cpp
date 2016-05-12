#include <GL/freeglut.h>
#include <include/game_engine.h>
#include <include/keyboard.h>
#include <include/transform_old.h>
#include "defines.h"

void getKeyboardDown(unsigned char key, int x, int y)
{
	gameEngine->keyboard->keyState[key] = true;
}

void getKeyboardUp(unsigned char key, int x, int y)
{
	gameEngine->keyboard->keyState[key] = false;
}

void getKeyboardSpecialDown(int key, int x, int y)
{
	gameEngine->keyboard->special[key] = true;
}

void getKeyboardSpecialUp(int key, int x, int y)
{
	gameEngine->keyboard->special[key] = false;
}
