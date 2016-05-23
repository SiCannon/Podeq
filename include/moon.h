#pragma once

#include <include/vector2f.h>
#include "satellite.h"

class Moon : public Satellite
{
public:
	Moon(Satellite *parent, glf mass, Warp *warp);
};