#pragma once

#include <include/timer.h>
#include "include/draw_task.h"

class Transform;

class BaseActor : public DrawTask
{
public:
	Transform *transform;
	BaseActor();
	~BaseActor();
	void draw();
	//virtual void update() { }
protected:
	//Timer *timer;
	virtual void draw_me() =0;
	void reset();
};
