#include "DirectionalLight.h"

namespace Processing
{
	DirectionalLight::DirectionalLight(float x, float y, float z, float r, float g, float b)
	{
		setDirection(x, y, z);
		setColor(r, g, b);
	}

	Utils::ColorTriad DirectionalLight::getColor()
	{
		return color;
	}

	void DirectionalLight::setColor(float r, float g, float b)
	{
		Utils::ColorTriad color(r, g, b);
		this->color = color;
	}

	Utils::Vec3 DirectionalLight::getDirection()
	{
		return coordinates;
	}

	void DirectionalLight::setDirection(float x, float y, float z)
	{
		Utils::Vec3 direction(x, y, z);
		coordinates = direction;
	}
}