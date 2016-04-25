#include <GL/freeglut.h>
#include "base_actor.h"
#include "monster.h"

Monster::Monster(Timer *timer) : BaseActor(timer)
{
	transform->rotation = 30.0f;;
}

void Monster::draw_me()
{
	GLubyte cols[] = { 0, 102, 255 };
	glColor3ubv(cols);

	GLfloat x = 5.0f;
	GLfloat monster_size = 1.0f;

	glBegin(GL_TRIANGLES);
	glVertex2f(x, 0);
	glVertex2f(x + monster_size, 0);
	glVertex2f(x + monster_size / 2.0f, monster_size);
	glEnd();
}

void Monster::update()
{

}
