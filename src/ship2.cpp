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
	warp = 1.0f;
	wasThrust = false;
	epochStartTime = -1;
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

#ifdef calculated_orbit

void Ship2::update(Timer * timer)
{
	if (isThrust)
	{
		glf rs = distanceSquared(game->planet->transform->trans(), transform->trans);
		GLfloat a = GravConstant * game->planet->mass / rs;
		GLfloat t = angleTo(transform->trans, game->planet->transform->trans());
		GLfloat ax = a * cosf(t);
		GLfloat ay = a * sinf(t);

		GLfloat force = ship_thrust;
		ax -= force * sinf(d_to_r(transform->rot));
		ay += force * cosf(d_to_r(transform->rot));

		v.x += ax * timer->intervalSeconds();
		v.y += ay * timer->intervalSeconds();

		transform->trans = transform->trans + v * timer->intervalSeconds();
		game->orbit->calc();
		wasThrust = true;
	}
	else
	{
		if (wasThrust)
		{
			wasThrust = false;
			game->orbit->calc();
			epochStartTime = timer->totalTicks;
		}
		else
		{
			if (epochStartTime == -1)
			{
				epochStartTime = timer->totalTicks;
			}
		}
		long t = timer->totalTicks - epochStartTime;
		game->orbit->calc_position(warp * t / 1000.0f);
		transform->trans = game->planet->transform->trans() + game->orbit->position_p;
		this->v = game->orbit->position_v;
	}
}

#else

void Ship2::update(Timer * timer)
{
	for (double w = 0; w < warp; w++)
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
	}

	

	//gameEngine->world_transform->translate_x = -transform->trans.x;
	//gameEngine->world_transform->translate_y = -transform->trans.y;

}

#endif

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

	glf warp_inc = 1.1f;

	if (keyboard->keyState[','])
	{
		warp /= warp_inc;
	}
	if (keyboard->keyState['.'])
	{
		warp *= warp_inc;
	}
	if (warp < 1.0f)
	{
		warp = 1.0f;
	}

	isThrust = !isWarp() && keyboard->special[GLUT_KEY_UP];
}

glf Ship2::speed()
{
	return v.length() * 100.0f;
}

bool Ship2::isWarp()
{
	return warp >= 1.5f;
}