#include <GL/freeglut.h>
#include <include/entity.h>
#include <include/gaf.h>
#include <include/gaf_util.h>
#include <include/gaf_math.h>
#include <include/game_engine.h>
#include <include/keyboard.h>
#include <include/polygon2f.h>
#include <include/timer.h>
#include <include/transform.h>
#include <include/vector2f.h>
#include "../include/start_params.h"
#include "../include/ship2.h"
#include "../include/podeq_game.h"
#include "../include/defines.h"

Ship2::Ship2(PodeqGame *game, Vector2f pos, Vector2f vel) : Entity(GL_TRIANGLES, 3, 3)
{
	this->game = game;
	transform->trans = pos;
	v = vel;
	create_ship();
}

void Ship2::create_ship()
{
	polygon->set_vertex(0, 0, ship_size * 2.0f);
	polygon->set_vertex(1, -ship_size, -ship_size);
	polygon->set_vertex(2, ship_size, -ship_size);

	polygon->set_index(0, 0);
	polygon->set_index(1, 1);
	polygon->set_index(2, 2);

	polygon->color = colorv(0, 128, 192);
}

void Ship2::update(Timer * timer)
{
	glf rs = distanceSquared(game->planet->transform->trans(), transform->trans);
	GLfloat a = GravConstant * game->planet->mass / rs;
	GLfloat t = angleTo(transform->trans, game->planet->transform->trans());
	GLfloat ax = a * cosf(t);
	GLfloat ay = a * sinf(t);

	if (isThrust)
	{
		GLfloat force = ship_thrust;
		ax -= force * sinf(d_to_r(transform->rot));
		ay += force * cosf(d_to_r(transform->rot));
	}

	v.x += ax * timer->intervalSeconds();
	v.y += ay * timer->intervalSeconds();

	transform->trans = transform->trans + v * timer->intervalSeconds();

	gameEngine->world_transform->translate_x = -transform->trans.x;
	gameEngine->world_transform->translate_y = -transform->trans.y;
}

void Ship2::input(Keyboard * keyboard)
{
	glf rotateInc = 5.0f;

	if (keyboard->special[GLUT_KEY_LEFT])
	{
		transform->rot += rotateInc;
	}
	if (keyboard->special[GLUT_KEY_RIGHT])
	{
		transform->rot -= rotateInc;
	}

	isThrust = keyboard->special[GLUT_KEY_UP];
}
