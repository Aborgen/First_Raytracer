#include "../DirectionalLight.h"

namespace Processing
{
	DirectionalLight::DirectionalLight(float x, float y, float z, float r, float g, float b) : Light(x, y, z, r, g, b)
	{
		setCoordinates(x, y, z);
		setColor(r, g, b);
	}

	Utils::Vec3 DirectionalLight::getDirection()
	{
		return getCoordinates();
	}

	void DirectionalLight::setDirection(float x, float y, float z)
	{
		setCoordinates(x, y, z);
	}
}