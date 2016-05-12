#pragma once
#include <include/transform_old.h>

class Mouse;

typedef void (*MouseEvent)(Mouse *mouse);

class Mouse
{
public:
	Mouse(Transform_Old *world_transform);
	int x;
	int y;
	void set(int x, int y);
	void process(int button, int state, int x, int y);
	MouseEvent onMouseLeftClick;
	MouseEvent onMouseWheelUp;
	MouseEvent onMouseWheelDown;
private:
	Transform_Old *world_transform;
};
