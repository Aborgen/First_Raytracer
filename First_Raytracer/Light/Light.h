#ifndef LIGHT_H
#define LIGHT_H
#pragma once

#include "../Utils/ColorTriad.h"
#include "../Utils/Vec3.h"

namespace Processing
{
	class Light
	{
	public:
		Light(float x, float y, float z, float r, float g, float b) {};
		virtual ~Light() {};
		virtual Utils::ColorTriad getColor() = 0;
		virtual void setColor(float x, float y, float z) = 0;

	protected:
		Utils::ColorTriad color;
		Utils::Vec3 coordinates;
	};
}

#endif // !LIGHT_H
