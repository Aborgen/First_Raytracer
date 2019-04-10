#ifndef LIGHT_H
#define LIGHT_H
#pragma once

#include "src/Attenuation.h";
#include "../Utils/ColorTriad.h"
#include "../Utils/Vec3.h"

namespace Processing
{
	class Light
	{
	public:
		Utils::ColorTriad getColor();
		void setColor(float r, float g, float b);
		Attenuation getAttenuation();
		void setAttenuation(float constant, float linear, float quadratic);

	protected:
		Light(float x, float y, float z, float r, float g, float b) {};
		Utils::Vec3 getCoordinates();
		void setCoordinates(float x, float y, float z);

	private:
		Utils::ColorTriad color;
		Utils::Vec3 coordinates;
		Attenuation attenuation;
	};
}

#endif // !LIGHT_H
