#include "PointLight.h"

namespace Processing
{
	PointLight::PointLight(float x, float y, float z, float r, float g, float b)
	{
		setLocation(x, y, z);
		setColor(r, g, b);
	}

	Utils::ColorTriad PointLight::getColor()
	{
		return color;
	}

	void PointLight::setColor(float r, float g, float b)
	{
		Utils::ColorTriad color(r, g, b);
		this->color = color;
	}

	Utils::Vec3 PointLight::getLocation()
	{
		return coordinates;
	}

	void PointLight::setLocation(float x, float y, float z)
	{
		Utils::Vec3 location(x, y, z);
		coordinates = location;
	}
}