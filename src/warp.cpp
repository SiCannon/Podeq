#include "warp.h"

#include <include/input_task.h>
#include <include/update_task.h>
#include <include/keyboard.h>
#include <include/timer.h>
#include "defines.h"

Warp::Warp()
{
	warp = 1.0f;
}

void Warp::input(Keyboard *keyboard)
{
	decrease_warp = keyboard->keyState[','];
	increase_warp = keyboard->keyState['.'];
	reset_warp = keyboard->keyState['/'];
}

void Warp::update(Timer *timer)
{
	glf warp_change = 1.0f + timer->intervalSeconds() * warp_control_sensitivity;

	if (decrease_warp)
	{
		warp /= warp_change;
	}
	if (increase_warp)
	{
		warp *= warp_change;
	}
	if (reset_warp)
	{
		warp = 1.0f;
	}
}
