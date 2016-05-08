#pragma once

#include "draw_task.h"
#include "Polygon2f.h"

class Polygon2f_Draw : public DrawTask
{
public:
	Polygon2f_Draw(Polygon2f *polygon);
	void draw();
private:
	Polygon2f *polygon;
};