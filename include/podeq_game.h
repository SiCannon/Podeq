#pragma once

#include <GL/freeglut.h>
#include "planet.h"
#include "ship.h"
#include "orbit_path.h"
#include "orbit.h"
#include "noise_test.h"
#include "test_objects.h"

class Ship2;
class Moon;
class Warp;
class Satellite;

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
	Satellite *moon;
	Satellite *moonlet;
	Warp *warp;
	Satellite *sun;

	Hex *hex;
	Tri *tri;
	CollisionDetector *cd;
private:
	Satellite *create_satellite(Satellite *parent, glf mass, Warp *warp, Vector2f position, Vector2f velocity, glf radius, GLubyte red, GLubyte green, GLubyte blue);
	void create_satellites();
};