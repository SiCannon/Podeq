#pragma once

#include "polygon2f.h"
//#include "base_actor.h"
#include "draw_task.h"

class Polygon2f_Draw : public DrawTask //BaseActor
{
public:
	Polygon2f_Draw(Polygon2f *polygon);
	void draw();
protected:
	void draw_me();
private:
	Polygon2f *polygon;
};