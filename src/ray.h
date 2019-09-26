#pragma once

#include "types.h"

/// Basic ray structure
struct Ray
{
	Vec3f	org;		///< Origin
	Vec3f	dir;		///< Direction
	float	t;			///< Current/maximum hit distance
};