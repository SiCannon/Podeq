#pragma once

#include <GL/freeglut.h>
#include "mouse.h"
#include <include/textutils.h>

#define orthoSize 10.0f

extern GLfloat rasterLeft;
extern GLfloat rasterBottom;
extern GLfloat rasterTop;
extern GLfloat aspect_ratio;

void reshape(int w, int h);
void screenToWorld(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *wx, GLfloat *wy);
void getBoardPos(Mouse *mouse, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *bx, GLfloat *by);
