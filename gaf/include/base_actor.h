#pragma once

#include <include/transform.h>
#include <include/timer.h>
#include "include/draw_task.h"

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
