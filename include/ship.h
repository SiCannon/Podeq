#pragma once

#include <include/timer.h>
#include <include/base_actor.h>
#include <include/update_task.h>
#include <include/input_task.h>
#include <include/keyboard.h>
#include "planet.h"

#define hist_size 70

class Ship : public BaseActor, public UpdateTask, public InputTask
{
public:
	GLfloat vx;
	GLfloat vy;
	Ship(GLfloat ivx, GLfloat ivy, Planet *planet);
protected:
	void draw_me();
private:
	Planet *planet;
    
    GLfloat hx[hist_size];
    GLfloat hy[hist_size];
    long lastHist;
    
    int hidx;
    int maxh;
    
	bool isThrust;
	GLfloat planetSurfacePosition;

    void update(Timer *timer);
	void input(Keyboard *keyboard);
    void save_history(Timer *timer);
	void calc_readings();
};