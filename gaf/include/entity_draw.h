#pragma once

#include <GL/freeglut.h>
#include "draw_task.h"
#include "entity.h"

class Entity_Draw : public DrawTask
{
public:
	Entity_Draw(Entity *entity);
	virtual void draw();
protected:
	Entity *entity;
};