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
#include "moon.h"
#include "satellite_draw.h"
#include "warp.h"

PodeqGame::PodeqGame()
{
	gameEngine->register_inputTask(new ExitOnEscape());
	gameEngine->register_inputTask(new PageToZoom(scale_mult));

	warp = new Warp();
	warp->warp = start_warp;
	gameEngine->register_inputTask(warp);
	gameEngine->register_updateTask(warp);

	create_satellites();

	ship2 = new Ship2(this, moon, { start_ship_x, start_ship_y }, { start_ship_vx, start_ship_vy }, warp);
	gameEngine->register_updateTask(ship2);
	gameEngine->register_inputTask(ship2);

	orbit_path = new OrbitPath(ship2->get_orbit());
	orbit_path->transform->trans = planet->position;

#ifndef hide_game_elements
	gameEngine->register_drawTask(planet);
	gameEngine->register_drawTask(orbit_path);
	gameEngine->register_drawTask(new Ship_Draw(ship2));
#endif

#ifndef calculated_orbit
	gameEngine->register_updateTask(orbit);
#endif

	auto sun = create_satellite(NULL, 1.0f, warp, { 10.0f, 10.0f }, { 0, 0 }, 0.1f, 255, 255, 0);
	auto mercury = create_satellite(sun, .1f, warp, { 10.0f, 10.4f }, { 1.5f, 0 }, 0.01f, 128, 0, 64);
	auto venus = create_satellite(sun, .1f, warp, { 10.0f, 10.8f }, { 1.0f, 0 }, 0.01f, 32, 128, 192);
	auto earth = create_satellite(sun, .1f, warp, { 10.0f, 11.8f }, { 0.8f, 0 }, 0.02f, 0, 128, 255);
	auto luna = create_satellite(earth, .1f, warp, { 10.0f, 11.9f }, { 0.8f, 0 }, 0.004f, 32, 192, 0);


	OrbitPredictor *op = new OrbitPredictor(orbit, planet);
	gameEngine->register_drawTask(op);


	Camera *camera = new Camera();

	camera->add_satellite(sun);

	camera->add_satellite(ship2);
	camera->add_satellite(planet);
	camera->add_satellite(moon);
	camera->add_satellite(moonlet);

	gameEngine->register_updateTask(camera);
	gameEngine->keyboard->register_keydown_handler(camera);

#ifdef show_debug_graph
	gameEngine->register_drawTask(new DebugGraph());
#endif

}

Satellite * PodeqGame::create_satellite(Satellite * parent, glf mass, Warp * warp, Vector2f position, Vector2f velocity, glf radius, GLubyte red, GLubyte green, GLubyte blue)
{
	Satellite *satellite = new Satellite(parent, mass, warp);
	if (parent != NULL)
	{
		parent->add_child(satellite);
	}
	satellite->position = position;
	satellite->velocity = velocity;
	satellite->recalc_orbit();

	if (parent != NULL)
	{
		gameEngine->register_updateTask(satellite);

		OrbitPath *orbit_path = new OrbitPath(satellite->get_orbit());
		orbit_path->transform->trans = satellite->position;
		gameEngine->register_drawTask(orbit_path);
	}

	gameEngine->register_drawTask(new SatelliteDraw(satellite, radius, red, green, blue));

	return satellite;
}

void PodeqGame::create_satellites()
{
	planet = new Planet(planet_mass, warp);
	planet->position.x = planet_x;
	planet->position.y = planet_y;

	moon = create_satellite(planet, 0.001f, warp, { 0, 3.0f }, { 0.035f, 0 }, 0.05f, 64, 64, 192);
	moonlet = create_satellite(moon, 0.00001f, warp, { 0, 3.1f }, { -0.1f, 0 }, 0.01f, 0, 128, 32);

	/*moon = new Satellite(planet, 0.001f, warp);
	moon->position = { 0, 3.0f };
	moon->velocity.x = 0.035f;
	moon->velocity.y = 0;
	moon->recalc_orbit();
	gameEngine->register_updateTask(moon);

	OrbitPath *moon_path = new OrbitPath(moon->get_orbit());
	moon_path->transform->trans = planet->position;
	gameEngine->register_drawTask(moon_path);
	gameEngine->register_drawTask(new SatelliteDraw(moon, 0.05f, 64, 64, 192));*/
	/*
	moonlet = new Moon(moon, 1.0f, warp);
	moonlet->position = { 0, 3.1f };
	moonlet->velocity.x = -.1f;
	moonlet->velocity.y = 0;
	moonlet->recalc_orbit();
	gameEngine->register_updateTask(moonlet);

	OrbitPath *moonlet_path = new OrbitPath(moonlet->get_orbit());
	moonlet_path->transform->trans = moonlet->position;
	gameEngine->register_drawTask(moonlet_path);
	gameEngine->register_drawTask(new SatelliteDraw(moonlet, 0.01f, 0, 128, 32));
	*/
}
