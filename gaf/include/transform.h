#pragma once

#include "gaf.h"
#include "vector2f.h"

class Transform
{
public:
	glf scale;
	glf rot;
	Vector2f trans;
	void applyTRS();
	void applyST();
};