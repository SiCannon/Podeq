#include <GL/freeglut.h>
#include <include/keyboard.h>
#include <include/timer.h>
#include <include/game_engine.h>
#include <include/vector2f.h>
#include "camera.h"
#include "ship2.h"
#include "planet.h"

#define max_focus 1

Camera::Camera(Ship2 *ship, Planet *planet)
{
	this->ship = ship;
	this->planet = planet;
	focus = 0;
}

void Camera::input(Keyboard *keyboard)
{

}

void Camera::update(Timer *timer)
{
	Vector2f p;

	switch (focus)
	{
		case 0:
			p.x = -ship->transform->trans.x;
			p.y = -ship->transform->trans.y;
			break;
		case 1:
			p.x = -planet->position.x;
			p.y = -planet->position.y;
			break;
	}

	gameEngine->world_transform->translate_x = p.x;
	gameEngine->world_transform->translate_y = p.y;
}

void Camera::on_keydown(int key, bool is_special)
{
	if (is_special && key == GLUT_KEY_HOME)
	{
		focus++;
		if (focus > max_focus)
		{
			focus = 0;
		}
	}
}
