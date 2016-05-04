#include <GL/freeglut.h>
#include <include/exit_on_escape.h>
#include <include/keyboard.h>

void ExitOnEscape::input(Keyboard *keyboard)
{
	if (keyboard->keyState[27])
	{
		glutLeaveMainLoop();
	}
}