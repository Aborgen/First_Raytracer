#include "../Light.h"

namespace Processing
{
	Light::Light(float x, float y, float z, float r, float g, float b, Type type)
	{
		Utils::Vec3 coordinates(x, y, z);
		Utils::ColorTriad color(r, g, b);
		Light(coordinates, color, type);
	}

	Utils::ColorTriad Light::getColor()
	{
		return color;
	}

	void Light::setColor(float r, float g, float b)
	{
		Utils::ColorTriad color(r, g, b);
		this->color = color;
	}

	Utils::Vec3 Light::getCoordinates()
	{
		return coordinates;
	}

	void Light::setCoordinates(float x, float y, float z)
	{
		Utils::Vec3 coordinates(x, y, z);
		this->coordinates = coordinates;
	}

	Attenuation Light::getAttenuation()
	{
		return attenuation;
	}

	void Light::setAttenuation(float constant, float linear, float quadratic)
	{
		Attenuation attenuation(constant, linear, quadratic);
		this->attenuation = attenuation;
	}

	Light::Type Light::getType()
	{
		return type;
	}
}