#pragma once

#include "polygon2f.h"
#include "base_actor.h"

class Polygon2f_Draw : public BaseActor
{
public:
	Polygon2f_Draw(Polygon2f *polygon);
protected:
	void draw_me();
private:
	Polygon2f *polygon;
};