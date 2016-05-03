#pragma once

#include <include/base_actor.h>

namespace Podeq
{
	class Ellipse : public BaseActor
	{
	public:
		Ellipse(Timer *timer);
		GLfloat xradius;
		GLfloat yradius;
	protected:
		void draw_me();
	};
}