#include <GL/freeglut.h>
#include <include/game_engine.h>
#include <include/keyboard.h>
#include <include/transform_old.h>
#include "defines.h"

void getKeyboardDown(unsigned char key, int x, int y)
{
	gameEngine->keyboard->set_keydown(key, false);
}

void getKeyboardUp(unsigned char key, int x, int y)
{
	gameEngine->keyboard->set_keyup(key, false);
}

void getKeyboardSpecialDown(int key, int x, int y)
{
	gameEngine->keyboard->set_keydown(key, true);
}

void getKeyboardSpecialUp(int key, int x, int y)
{
	gameEngine->keyboard->set_keyup(key, true);
}

void Keyboard::register_keydown_handler(Keydown_Handler *handler)
{
	keydown_handlers.push_back(handler);
}

void Keyboard::set_keydown(int key, bool is_special)
{
	if (is_special)
	{
		special[key] = true;
	}
	else
	{
		keyState[key] = true;
	}
	call_keydown_handlers(key, is_special);
}

void Keyboard::set_keyup(int key, bool is_special)
{
	if (is_special)
	{
		special[key] = false;
	}
	else
	{
		keyState[key] = false;
	}
}

void Keyboard::call_keydown_handlers(int key, bool is_special)
{
	for (unsigned int i = 0; i < keydown_handlers.size(); i++)
	{
		keydown_handlers[i]->on_keydown(key, is_special);
	}
}
