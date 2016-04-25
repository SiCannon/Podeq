#pragma once

#include "timer.h"
#include "base_actor.h"

#define hist_size 70

class Ship : public BaseActor
{
public:
    Ship(Timer *timer, GLfloat ivx, GLfloat ivy);
    void accel(GLfloat ax, GLfloat ay);
protected:
	void draw_me();
private:
    GLfloat vx;
    GLfloat vy;
    
    GLfloat hx[hist_size];
    GLfloat hy[hist_size];
    long lastHist;
    
    int hidx;
    int maxh;
    
    void update();
    void save_history();
};