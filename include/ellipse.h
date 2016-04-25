#pragma once

#include "base_actor.h"

class Ellipse : public BaseActor
{
public:
	Ellipse(Timer *timer);
	GLfloat xradius;
	GLfloat yradius;
protected:
	void draw_me();
};
