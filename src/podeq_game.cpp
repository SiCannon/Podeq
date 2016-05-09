#include "../include/podeq_game.h"
#include "../include/start_params.h"
#include "planet.h"
#include "ship.h"
#include "orbit_path.h"
#include "orbit.h"
#include <include/game_engine.h>
#include <include/exit_on_escape.h>
#include <include/page_to_zoom.h>
#include "test_objects.h"

PodeqGame::PodeqGame()
{
	gameEngine->register_inputTask(new ExitOnEscape());
	gameEngine->register_inputTask(new PageToZoom(scale_mult));

	planet = new Planet(planet_mass);
	planet->transform->translate_x = planet_x;
	planet->transform->translate_y = planet_y;

	ship = new Ship(start_ship_vx, start_ship_vy, planet);
	ship->transform->translate_x = start_ship_x;
	ship->transform->translate_y = start_ship_y;

	orbit = new Orbit(planet, ship);
	orbit->calc(planet_x, planet_y, start_ship_x, start_ship_y, start_ship_vx, start_ship_vy, planet->GM());

	orbit_path = new OrbitPath(orbit);
	orbit_path->transform->translate_x = planet_x;
	orbit_path->transform->translate_y = planet_y;

	/*
	gameEngine->register_drawTask(planet);
	gameEngine->register_drawTask(orbit_path);
	gameEngine->register_drawTask(ship);
	
	gameEngine->register_updateTask(orbit);
	gameEngine->register_updateTask(ship);

	gameEngine->register_inputTask(ship);
	//*/

	/*noise_test = new NoiseTest();
	gameEngine->register_drawTask(noise_test);
	gameEngine->register_inputTask(noise_test);*/

	hex = new Hex();
	tri = new Tri();
	cd = new CollisionDetector(hex, tri);

	gameEngine->register_drawTask(hex->polydraw);
	gameEngine->register_drawTask(tri->polydraw);
	gameEngine->register_updateTask(cd);
}
