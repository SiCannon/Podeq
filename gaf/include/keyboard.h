#pragma once

#include <vector>
#include <include/keydown_handler.h>
class Keyboard;

//typedef void(*GafKeyEvent)(int key, bool is_special);

class Keyboard
{
public:
	
	bool keyState[256];
	bool special[256];
	void register_keydown_handler(Keydown_Handler *handler);
	void set_keydown(int key, bool is_special);
	void set_keyup(int key, bool is_special);
private:
	std::vector<Keydown_Handler*> keydown_handlers;
	void call_keydown_handlers(int key, bool is_special);
};

void getKeyboardDown(unsigned char key, int x, int y);
void getKeyboardUp(unsigned char key, int x, int y);
void getKeyboardSpecialDown(int key, int x, int y);
void getKeyboardSpecialUp(int key, int x, int y);
