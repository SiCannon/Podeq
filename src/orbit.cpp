#include <math.h>
#include <include/gaf_math.h>
#include <include/transform_old.h>
#include "orbit.h"
#include "omech.h"
#include "ship2.h"
#include "planet.h"
#include "satellite.h"
#include "defines.h"

#ifdef use_satellites
Orbit::Orbit(Satellite *parent, Satellite *child)
{
	this->parent = parent;
	this->child = child;
}
#else
Orbit::Orbit(Planet *planet, Ship2 *ship)
{
	this->planet = planet;
	this->ship = ship;
}
#endif

void Orbit::calc(glf rx, glf ry, glf vx, glf vy, glf GM)
{
	glf r = sqrtf(SQR(rx) + SQR(ry));
	glf vsq = SQR(vx) + SQR(vy);
	glf phi = PI_BY_2 - angleBetween(rx, ry, vx, vy);
	
	e = calc_e(r, vsq, GM, phi);
	a = calc_a(r, vsq, GM);
	Rp = calc_Rp(a, e);
	Ra = calc_Ra(a, e);
	nu = calc_nu(r, vsq, GM, phi);
	if (e <= 1.0f)
	{
		mean_motion = calc_n(GM, a);
	}
	else
	{
		mean_motion = calc_n(GM, fabsf(a));
	}

	if (nu < 0)
	{
		nu += TWO_PI;
	}

	glf r_angle = angleBetween(1.0f, 0.0f, rx, ry);
	angle = r_angle - (nu - PI);

	angle = normalize_angle(angle);
}

void Orbit::calc(glf planet_x, glf planet_y, glf ship_x, glf ship_y, glf vx, glf vy, glf GM)
{
    glf rx = ship_x - planet_x;
    glf ry = ship_y - planet_y;
    calc(rx, ry, vx, vy, GM);
}

void Orbit::calc()
{
#ifdef use_satellites
	calc(
		parent->position.x,
		parent->position.y,
		child->position.x,
		child->position.y,
		child->velocity.x,
		child->velocity.y,
		parent->GM()
	);
#else
	calc(
		planet->position.x,
		planet->position.y,
		ship->transform->trans.x,
		ship->transform->trans.y,
		ship->velocity.x,
		ship->velocity.y,
		planet->GM()
	);
#endif
}

void Orbit::update(Timer *timer)
{
	calc();
}

bool Orbit::is_hyperbolic()
{
	return e >= 1.0f;
}

Vector2f Orbit::position_at_time(glf t)
{
	// version 1
	/*
	glf M = mean_motion * t;
	glf E = M;
	glf next_term;
	do
	{
		next_term = (E - e * sinf(E) - M) / (1 - e * cosf(E));
		E = E - next_term;
	} while (next_term > 0);
	glf true_anomaly = acosf((cosf(E) - e) / (1 - e * cosf(E)));
	*/

	// version 2
	calc_position(t);
	return position_p;
}

void Orbit::calc_position(GLfloat t)
{
	glf M0 = TrueToMeanAnomalyf(e, nu);
	glf M1 = mean_motion * t + M0;
	glf true_anomaly = MeanToTrueAnomalyf(e, M1);

	glf r = calc_r(a, e, true_anomaly);
	glf theta = true_anomaly - (PI - angle);

	position_p = { r * cosf(theta), r * sinf(theta) };
	position_phi = calc_phi(e, true_anomaly);
#ifdef use_satellites
	position_speed = calc_v(parent->GM(), r, a);
#else
	position_speed = calc_v(planet->GM(), r, a);
#endif
	//position_theta = PI_BY_2 - (true_anomaly + angle + position_phi - TWO_PI);
	position_theta = (PI_BY_2 - position_phi) + true_anomaly - (PI - angle);
	position_v = Vector2f::from_polar(position_speed, position_theta);
}