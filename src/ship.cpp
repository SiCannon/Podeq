#include <GL/freeglut.h>
#include "ship.h"
#include <include/shapes.h>
#include "timer.h"
#include "planet.h"
#include "gaf_math.h"
#include "defines.h"

Ship::Ship(GLfloat ivx, GLfloat ivy, Planet *planet) : BaseActor()
{
	this->planet = planet;
    vx = ivx;
    vy = ivy;
    hidx = -1;
    maxh = -1;
}

void Ship::draw_me()
{
    
    
    GLfloat radius = 0.1f;
    
    glColor4ub(0, 192, 0, 100);
    
    glSolidCircle(radius, 12);
    
    //glPushMatrix();
    for (int i = 0; i <= maxh; i++)
    {
		//glPushMatrix();
		//glLoadIdentity();
		reset();
        int dh = (i <= hidx) ? (hidx - i) : (hidx + hist_size - i);
        GLfloat dhf = 1.0f - ((float)dh / (float)hist_size);
        GLubyte c = (int) (dhf * 192.0f); 
        glColor4ub(0, c, 0, 0);
        //glLoadIdentity();
        glTranslatef(hx[i], hy[i], 0);
        glSolidCircle(0.05f, 3);
		//glPopMatrix();
	}
    //glPopMatrix();
    
}

void Ship::update(Timer *timer)
{
	save_history(timer);

	GLfloat rs = distanceSquared(planet->transform, transform);
	GLfloat a = GravConstant * planet->mass / rs;
	GLfloat t = angleTo(transform, planet->transform);
	GLfloat ax = a * cos(t);
	GLfloat ay = a * sin(t);

	vx += ax * timer->intervalSeconds();
	vy += ay * timer->intervalSeconds();

    GLfloat dx = vx * timer->intervalSeconds();
    GLfloat dy = vy * timer->intervalSeconds();
    transform->translate_x += dx;
    transform->translate_y += dy;
}

void Ship::save_history(Timer *timer)
{
    if ((timer->totalTicks - lastHist) < 100)
    {
        return;
    }
    lastHist = timer->totalTicks;
    
    hidx++;
    if (hidx >= hist_size)
    {
        hidx = 0;
    }
    if (hidx > maxh)
    {
        maxh = hidx;
    }
    
    hx[hidx] = transform->translate_x;
    hy[hidx] = transform->translate_y;
}