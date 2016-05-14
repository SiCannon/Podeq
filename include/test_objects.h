#pragma once

#include <include/polygon2f.h>
#include <include/polygon2f_draw.h>
#include <include/update_task.h>
#include <include/draw_task.h>
#include <include/input_task.h>

class Hex
{
public:
	Polygon2f *poly;
	Polygon2f_Draw *polydraw;
	Hex();
};

class Tri
{
public:
	Polygon2f *poly;
	Polygon2f_Draw *polydraw;
	Tri();
};

class CollisionDetector : public UpdateTask, public DrawTask, public InputTask
{
public:
	CollisionDetector(Hex *hex, Tri *tri);
	Hex *hex;
	Tri *tri;
	virtual void update(Timer * timer) override;
	virtual void draw() override;
	virtual void input(Keyboard *keyboard) override;
	bool is_collision;
};

class Hyperbola : public DrawTask
{
public:
	void draw();
}