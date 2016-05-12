#include <GL/freeglut.h>
#include <include/transform_old.h>
#include <include/base_actor.h>
#include <include/timer.h>

BaseActor::BaseActor()
{
	//this->timer = timer;
	
	transform = new Transform_Old();
	transform->scale = 1.0f;
}

BaseActor::~BaseActor()
{
	delete(transform);
}

void BaseActor::draw()
{
	glPushMatrix();
	//reset();
	transform->applyTRS();
	draw_me();
	glPopMatrix();
}

void BaseActor::reset()
{
	//glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	//transform->applyTRS();
}