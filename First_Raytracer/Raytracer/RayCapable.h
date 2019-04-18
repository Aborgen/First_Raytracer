#ifndef RAYCAPABLE_H
#define RAYCAPABLE_H
#pragma once

#include "../Ray/Ray.h"
#include "../Utils/Vec3.h"

namespace Processing
{
	class RayCapable
	{
	public:
		virtual Ray castRay(Utils::Vec3 direction);

	protected:
		RayCapable() {};
		Utils::Vec3 position;
	};
}

#endif // !RAYCAPABLE_H
