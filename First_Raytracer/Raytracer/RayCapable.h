#ifndef RAYCAPABLE_H
#define RAYCAPABLE_H
#pragma once

#include "../Ray/Ray.h"
#include "../Utils/Vec3.h"
#include "../Screen/Screen.h"

namespace Processing
{
	class RayCapable
	{
	public:
		virtual Ray castRay(float rasterX, float rasterY) = 0;

	protected:
		RayCapable() {};
		Utils::Vec3 position;
		float offset;

	private:
		virtual Utils::Vec3 generateDirection(float rasterX, float rasterY) = 0;
	};
}

#endif // !RAYCAPABLE_H
