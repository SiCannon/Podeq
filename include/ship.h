#pragma once

#include "timer.h"
#include "base_actor.h"
#include "include/update_task.h"
#include "planet.h"

#define hist_size 70

class Ship : public BaseActor, public UpdateTask
{
public:
    Ship(GLfloat ivx, GLfloat ivy, Planet *planet);
protected:
	void draw_me();
private:
	Planet *planet;

    GLfloat vx;
    GLfloat vy;
    
    GLfloat hx[hist_size];
    GLfloat hy[hist_size];
    long lastHist;
    
    int hidx;
    int maxh;
    
    void update(Timer *timer);
    void save_history(Timer *timer);
};