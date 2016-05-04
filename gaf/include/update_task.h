#pragma once

#include <include/timer.h>

class UpdateTask
{
public:
	virtual void update(Timer *timer) = 0;
};