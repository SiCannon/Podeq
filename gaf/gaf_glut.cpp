#include <GL/freeglut.h>
#include "screenutil.h"
#include "keyboard.h"
#include "game_engine.h"

#define INITIAL_WINDOW_LEFT 50
#define INITIAL_WINDOW_TOP 50
#define INTIAL_WNDOW_WIDTH 800
#define INITIAL_WINDOW_HEIGHT 600

void init_glut(int argc, char **argv, const char *title, void(*display)(void))
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	glutInitWindowPosition(INITIAL_WINDOW_LEFT, INITIAL_WINDOW_TOP);
	glutInitWindowSize(INTIAL_WNDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
	glutCreateWindow(title);

	glutDisplayFunc(display);
	//glutDisplayFunc(main_game_loop);
	glutReshapeFunc(reshape);
	//glutPassiveMotionFunc(saveMousePosition);
	//glutMotionFunc(saveMousePosition);
	//glutMouseFunc(processMouse);
	glutKeyboardFunc(getKeyboardDown);
	glutKeyboardUpFunc(getKeyboardUp);
	//glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();
}