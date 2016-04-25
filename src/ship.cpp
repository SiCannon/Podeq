#include <GL/freeglut.h>
#include "ship.h"
#include "shapes.h"

Ship::Ship(Timer *timer, GLfloat ivx, GLfloat ivy) : BaseActor(timer)
{
    vx = ivx;
    vy = ivy;
    hidx = -1;
    maxh = -1;
}

void Ship::draw_me()
{
    update();
    save_history();
    
    GLfloat radius = 0.1f;
    
    glColor3ub(0, 192, 0);
    
    glSolidCircle(radius, 12);
    
    glPushMatrix();
    for (int i = 0; i <= maxh; i++)
    {
        glLoadIdentity();
        int dh = (i <= hidx) ? (hidx - i) : (hidx + hist_size - i);
        GLfloat dhf = 1.0f - ((float)dh / (float)hist_size);
        GLubyte c = (int) (dhf * 192.0f); 
        glColor3ub(0, c, 0);
        glLoadIdentity();
        glTranslatef(hx[i], hy[i], 0);
        glSolidCircle(0.05f, 3);
    }
    glPopMatrix();
    
}

void Ship::update()
{
    GLfloat dx = vx * timer->intervalSeconds();
    GLfloat dy = vy * timer->intervalSeconds();
    transform->translate_x += dx;
    transform->translate_y += dy;
}

void Ship::accel(GLfloat ax, GLfloat ay)
{
    vx += ax * timer->intervalSeconds();
    vy += ay * timer->intervalSeconds();
}

void Ship::save_history()
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