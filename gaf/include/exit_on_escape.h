#pragma once

#include "input_task.h"
#include <include/keyboard.h>

class ExitOnEscape : public InputTask
{
public:
	void input(Keyboard *keyboard);
};