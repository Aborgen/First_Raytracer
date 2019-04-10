#include "../PointLight.h"

namespace Processing
{
	PointLight::PointLight(float x, float y, float z, float r, float g, float b) : Light(x, y, z, r, g, b)
	{
		setCoordinates(x, y, z);
		setColor(r, g, b);
	}

	Utils::Vec3 PointLight::getLocation()
	{
		return getCoordinates();
	}

	void PointLight::setLocation(float x, float y, float z)
	{
		setCoordinates(x, y, z);
	}
}