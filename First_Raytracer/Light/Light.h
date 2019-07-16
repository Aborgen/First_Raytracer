#ifndef LIGHT_H
#define LIGHT_H
#pragma once

#include "src/Attenuation.h"
#include "../Utils/ColorTriad.h"
#include "../Utils/Vec3.h"

namespace Processing
{
	class Light
	{
	public:
		enum class Type { DIRECTIONAL, POINT };
		Utils::ColorTriad getColor();
		void setColor(float r, float g, float b);
		Attenuation getAttenuation();
		void setAttenuation(float constant, float linear, float quadratic);
		void setAttenuation(const Attenuation &attenuation);
		Type getType();
		Utils::Vec3 getCoordinates();
		void setCoordinates(float x, float y, float z);

	protected:
		Light(float x, float y, float z, float r, float g, float b, Type type) : coordinates(x, y, z), color(r, g, b), type(type) {};

	private:
		Utils::Vec3 coordinates;
		Utils::ColorTriad color;
		Attenuation attenuation;
		const Type type;
	};
}

#endif // !LIGHT_H
