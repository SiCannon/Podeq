#include <GL/freeglut.h>
#include <math.h>
#include <include/screenutil.h>
#include <include/mouse.h>

GLfloat rasterLeft = 0;
GLfloat rasterBottom = 0;
GLfloat rasterTop = 0;
GLfloat aspect_ratio = 0;

int windowWidth;
int windowHeight;

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspect_ratio = (GLfloat)w / (GLfloat)h;
	glOrtho(-orthoSize * aspect_ratio, orthoSize * aspect_ratio, -orthoSize, orthoSize, -1, 1);

	rasterBottom = -orthoSize;
	rasterTop = orthoSize;
	rasterLeft = -orthoSize * aspect_ratio;
}

void screenToWorld(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *wx, GLfloat *wy)
{
	GLfloat aspect_ratio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	GLfloat orthoHeight = orthoSize / scale;
	GLfloat orthoWidth = orthoHeight * aspect_ratio;

	*wx = 2.0f * orthoWidth * (GLfloat)x / (GLfloat)windowWidth - orthoWidth - trans_x;
	*wy = orthoHeight - 2.0f * orthoHeight * (GLfloat)y / (GLfloat)windowHeight - trans_y; // shouldn't this be  + trans_y ??
}


void getBoardPos(Mouse *mouse, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *bx, GLfloat *by)
{
	GLfloat mx, my;
	screenToWorld(mouse->x, mouse->y, scale, trans_x, trans_y, &mx, &my);
	*bx = floorf(mx);
	*by = floorf(my);
}

