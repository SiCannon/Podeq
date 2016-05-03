#pragma once

#include "planet.h"
#include "ship.h"
#include "orbit_path.h"
#include "orbit.h"

class PodeqGame
{
public:
	PodeqGame();
	Planet *planet;
	Ship *ship;
	OrbitPath *orbit_path;
	Orbit *orbit;
};