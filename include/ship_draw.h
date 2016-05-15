#pragma once

#include <include/entity_draw.h>

class Ship2;

class Ship_Draw : public Entity_Draw
{
public:
	Ship_Draw(Ship2 *ship);
	void draw() override;
private:
	Ship2 *hud_ship;
	Entity_Draw *hud_ship_draw;
	void create_hud();
	void draw_hud();
	void draw_reticule();
};