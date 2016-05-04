#pragma once

class Keyboard
{
public:
	bool keyState[256];
	bool special[256];
};

void getKeyboardDown(unsigned char key, int x, int y);
void getKeyboardUp(unsigned char key, int x, int y);
void getKeyboardSpecialDown(int key, int x, int y);
void getKeyboardSpecialUp(int key, int x, int y);


