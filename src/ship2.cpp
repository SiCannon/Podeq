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
#include "../include/warp.h"

Ship2::Ship2(PodeqGame *game, Satellite *orbiting, Vector2f pos, Vector2f vel, Warp *warp) : Entity(GL_TRIANGLES, 3, 3), Satellite(orbiting, 0, warp)
{
	this->game = game;
#ifdef use_satellites
	position = pos;
#else
	transform->trans = pos;
#endif
	velocity = vel;
	create_ship();
	recalc_orbit();
	//warp = start_warp;
	wasThrust = false;
	lastUpdateTime = 0;
}

void print_vector(const char *title, Vector2f v)
{
	printf(title);
	//printf(": (%.8f, %.8f)\n", v.x, v.y);
	printf(": %.8f\n", v.length());
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
	glf time = timer->intervalSeconds() * warp->warp;

	if (isThrust || wasThrust)
	{
		perform_thrust(timer, time);
	}

	if (isThrust)
	{
		wasThrust = true;
	}
	else
	{
		if (wasThrust)
		{
			wasThrust = false;
			get_orbit()->calc();
			get_orbit()->calc_position(0);
			position = parent->position + get_orbit()->position_p;
			velocity = get_orbit()->position_v;
			lastUpdateTime = 0;
		}
		else
		{
			Satellite::update(timer);
		}
	}

	change_parent_body();
}

#else

void Ship2::update(Timer * timer)
{
	for (double w = 0; w < warp; w++)
	{
		glf rs = distanceSquared(parent->position(), transform->trans);
		GLfloat a = GravConstant * parent->mass / rs;
		GLfloat t = angleTo(transform->trans, parent->position());
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

	/*glf warp_inc = 1.1f;

	if (keyboard->keyState[','])
	{
		warp /= warp_inc;
	}
	if (keyboard->keyState['.'])
	{
		warp *= warp_inc;
	}
	if (keyboard->keyState['/'])
	{
		warp = 1.0f;
	}
	if (warp < 0.0f)
	{
		warp = 0.0f;
	}*/

	isThrust = keyboard->special[GLUT_KEY_UP];
}

glf Ship2::speed()
{
	return velocity.length() * 100.0f;
}

bool Ship2::isWarp()
{
	return warp->warp >= 1.5f;
}

void Ship2::perform_thrust(Timer *timer, glf time)
{
	glf rs = distanceSquared(parent->position, position);
	GLfloat a = GravConstant * parent->mass / rs;
	GLfloat t = angleTo(position, parent->position);
	GLfloat ax = a * cosf(t);
	GLfloat ay = a * sinf(t);

	GLfloat force = ship_thrust;
	ax -= force * sinf(d_to_r(transform->rot));
	ay += force * cosf(d_to_r(transform->rot));

	velocity.x += ax * timer->intervalSeconds();
	velocity.y += ay * timer->intervalSeconds();

	position = position + (absolute_velocity() * time);
	get_orbit()->calc();
	//get_orbit()->calc_position(0);
}

bool is_in_soi(Ship2 *ship, Satellite *satellite)
{
	glf r_ship = (ship->position - satellite->position).length();
	glf r_soi = satellite->sphere_of_influence();
	return r_ship <= r_soi;
}

Satellite *find_root(Satellite *s)
{
	while (s->parent != NULL)
	{
		s = s->parent;
	}
	return s;
}

void Ship2::change_parent_body()
{
	// assume siblings never have overlapping SOIs
	// therefore overlapping SOIs are striclty hierarchical
	// which means we need to find the deepest SOI working from the current one down

	// find the sun
	Satellite *soi = find_root(this);

	// find which child we are in, if any
	bool found_one;
	do
	{
		found_one = false;
		for (int i = 0; i < soi->children.size(); i++)
		{
			if (is_in_soi(this, soi->children[i]))
			{
				soi = soi->children[i];
				found_one = true;
			}
		}
	} while (found_one);

	if (soi != parent)
	{
		Vector2f v = absolute_velocity();
		parent = soi;
		velocity = v - parent->absolute_velocity();
		orbit->set_parent(parent);

		get_orbit()->calc();
		get_orbit()->calc_position(0);
		position = parent->position + get_orbit()->position_p;
		velocity = get_orbit()->position_v;
		lastUpdateTime = 0;
	}
}
