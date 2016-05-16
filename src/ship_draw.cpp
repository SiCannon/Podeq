#include <include/gaf.h>
#include <include/gaf_util.h>
#include <include/game_engine.h>
#include <include/vector2f.h>
#include <include/screenutil.h>
#include <include/textutils.h>
#include "../include/ship_draw.h"
#include "../include/ship2.h"

Ship_Draw::Ship_Draw(Ship2 *ship) : Entity_Draw(ship)
{
	this->ship = ship;
	create_hud();
}

void Ship_Draw::create_hud()
{
	hud_ship = new Ship2(NULL, { 0, 0 }, { 0, 0 });
	hud_ship->transform->scale = 40.0f;
	hud_ship->polygon->color = colorv(0, 192, 255);
	hud_ship_draw = new Entity_Draw(hud_ship);
}

void Ship_Draw::draw()
{
	Entity_Draw::draw();

	draw_hud();

	if (gameEngine->world_transform->scale < 8.0f)
	{
		draw_reticule();
	}
}

void Ship_Draw::draw_hud()
{
	glPushMatrix();
	glLoadIdentity();

	hud_ship->transform->trans = { -rasterLeft - 1.0f, rasterBottom + 1.0f };
	hud_ship->transform->rot = entity->transform->rot;
	hud_ship_draw->draw();

	glLoadIdentity();
	glColor3ub(32, 150, 32);
	textReset(2);
	textOut("speed:");
	textOutFloat(ship->speed());

	glPopMatrix();
}

void Ship_Draw::draw_reticule()
{
	glPushMatrix();
	glLoadIdentity();

	glf rd = 0.2f;
	glf rs = 0.1f;

	glColor3ub(0, 128, 0);

	glBegin(GL_LINES);

	glVertex2f(rd, rd - rs);
	glVertex2f(rd, rd);
	glVertex2f(rd, rd);
	glVertex2f(rd - rs, rd);

	glVertex2f(-rd + rs, rd);
	glVertex2f(-rd, rd);
	glVertex2f(-rd, rd);
	glVertex2f(-rd, rd - rs);

	glVertex2f(-rd, -rd + rs);
	glVertex2f(-rd, -rd);
	glVertex2f(-rd, -rd);
	glVertex2f(-rd + rs, -rd);

	glVertex2f(rd - rs, -rd);
	glVertex2f(rd, -rd);
	glVertex2f(rd, -rd);
	glVertex2f(rd, -rd + rs);

	glEnd();

	glPopMatrix();
}