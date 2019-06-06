#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#pragma once

#include "Light.h"

namespace Processing
{
	class PointLight : public Light
	{
	public:
		PointLight(float x, float y, float z, float r, float g, float b, Type type) : Light(x, y, z, r, g, b, type) {};
		Utils::Vec3 getLocation();
		void setLocation(float x, float y, float z);
	};
}

#endif // !POINTLIGHT_H
