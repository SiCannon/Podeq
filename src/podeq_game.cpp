#include "../include/podeq_game.h"
#include "../include/start_params.h"
#include "planet.h"
#include "ship.h"
#include "orbit_path.h"
#include "orbit.h"
#include <include/game_engine.h>
#include <include/exit_on_escape.h>
#include <include/page_to_zoom.h>
#include <include/polygon2f_draw.h>
#include <include/entity_draw.h>
#include "test_objects.h"
#include "ship2.h"
#include "ship_draw.h"
#include "camera.h"
#include "defines.h"
#include "debug_graph.h"

PodeqGame::PodeqGame()
{
	gameEngine->register_inputTask(new ExitOnEscape());
	gameEngine->register_inputTask(new PageToZoom(scale_mult));

	planet = new Planet(planet_mass);
	planet->position.x = planet_x;
	planet->position.y = planet_y;

	//ship = new Ship(start_ship_vx, start_ship_vy, planet);
	//ship->transform->translate_x = start_ship_x;
	//ship->transform->translate_y = start_ship_y;

	ship2 = new Ship2(this, { start_ship_x, start_ship_y }, { start_ship_vx, start_ship_vy });
	//ship2->transform->rot = 45.0f;
	
	gameEngine->register_updateTask(ship2);
	gameEngine->register_inputTask(ship2);

	orbit = new Orbit(planet, ship2);
	orbit->calc();

	orbit_path = new OrbitPath(orbit);
	orbit_path->transform->trans.x = planet_x;
	orbit_path->transform->trans.y = planet_y;

#ifndef hide_game_elements
	gameEngine->register_drawTask(planet);
	gameEngine->register_drawTask(orbit_path);
	gameEngine->register_drawTask(new Ship_Draw(ship2));
#endif

#ifndef calculated_orbit
	gameEngine->register_updateTask(orbit);
#endif

	//gameEngine->register_updateTask(ship);

	//gameEngine->register_inputTask(ship);
	//*/

	/*noise_test = new NoiseTest();
	gameEngine->register_drawTask(noise_test);
	gameEngine->register_inputTask(noise_test);*/

	/*
	hex = new Hex();
	tri = new Tri();
	cd = new CollisionDetector(hex, tri);

	gameEngine->register_drawTask(hex->polydraw);
	gameEngine->register_drawTask(tri->polydraw);
	gameEngine->register_updateTask(cd);
	gameEngine->register_drawTask(cd);
	gameEngine->register_inputTask(cd);
	//*/


	/*Hyperbola *hyper = new Hyperbola(orbit);
	gameEngine->register_drawTask(hyper);
	gameEngine->register_inputTask(hyper);
	gameEngine->register_updateTask(hyper);*/

	OrbitPredictor *op = new OrbitPredictor(orbit, planet);
	gameEngine->register_drawTask(op);


	Camera *camera = new Camera(ship2, planet);
	gameEngine->register_updateTask(camera);
	gameEngine->keyboard->register_keydown_handler(camera);

#ifdef show_debug_graph
	gameEngine->register_drawTask(new DebugGraph());
#endif
}
