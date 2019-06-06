#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#pragma once

#include "Light.h"

namespace Processing
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(float x, float y, float z, float r, float g, float b, Type type) : Light(x, y, z, r, g, b, Type::DIRECTIONAL) {};
		Utils::Vec3 getDirection();
		void setDirection(float x, float y, float z);
	};
}

#endif // !DIRECTIONALLIGHT_H
