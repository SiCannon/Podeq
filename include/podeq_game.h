#pragma once

#include "planet.h"
#include "ship.h"
#include "orbit_path.h"
#include "orbit.h"
#include "noise_test.h"
#include "test_objects.h"

class Ship2;

class PodeqGame
{
public:
	PodeqGame();
	Planet *planet;
	Ship *ship;
	OrbitPath *orbit_path;
	Orbit *orbit;
	NoiseTest *noise_test;
	Ship2 *ship2;

	Hex *hex;
	Tri *tri;
	CollisionDetector *cd;
};