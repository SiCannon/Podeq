#pragma once

#include <include/vector2f.h>
#include "has_position.h"

class HasPositionAndVelocity : public HasPosition
{
public:
	//virtual inline Vector2f get_velocity() = 0;
	Vector2f velocity;
};