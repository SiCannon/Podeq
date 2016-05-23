#pragma once

#include "planet.h"
#include "ship.h"
#include "orbit_path.h"
#include "orbit.h"
#include "noise_test.h"
#include "test_objects.h"

class Ship2;
class Moon;
class Warp;

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
	Moon *moon;
	Warp *warp;

	Hex *hex;
	Tri *tri;
	CollisionDetector *cd;
};