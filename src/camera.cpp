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
	new_style = false;
}

Camera::Camera()
{
	focus = 0;
	new_style = true;
}

void Camera::add_satellite(Satellite * s)
{
	satellites.push_back(s);
}

void Camera::input(Keyboard *keyboard)
{

}

void Camera::update(Timer *timer)
{
	Vector2f p;

	if (new_style)
	{
		p = -satellites[focus]->position;
	}
	else
	{
		switch (focus)
		{
		case 0:
			p.x = -ship->position.x;
			p.y = -ship->position.y;
			break;
		case 1:
			p.x = -planet->position.x;
			p.y = -planet->position.y;
			break;
		}
	}

	gameEngine->world_transform->translate_x = p.x;
	gameEngine->world_transform->translate_y = p.y;
}

void Camera::on_keydown(int key, bool is_special)
{
	int max = new_style ? satellites.size() - 1 : max_focus;

	if (is_special && key == GLUT_KEY_HOME)
	{
		focus++;
		if (focus > max)
		{
			focus = 0;
		}
	}
}
