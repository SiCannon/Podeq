#pragma once

#include <include/keyboard.h>

class InputTask
{
public:
	virtual void input(Keyboard *keyboard) = 0;
};