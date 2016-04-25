#pragma once

class Timer
{
public:
	Timer();
	long totalTicks;
	long intervalTicks;
	void tick();
	GLfloat intervalSeconds();
private:
	bool started;
};
