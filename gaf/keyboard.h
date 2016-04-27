#pragma once

#include "transform.h"

class Keyboard
{
public:
	bool keyState[256];
};

void getKeyboardDown(unsigned char key, int x, int y);
void getKeyboardUp(unsigned char key, int x, int y);


