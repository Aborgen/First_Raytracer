#include "../PointLight.h"

namespace Processing
{
	Utils::Vec3 PointLight::getLocation()
	{
		return getCoordinates();
	}

	void PointLight::setLocation(float x, float y, float z)
	{
		setCoordinates(x, y, z);
	}
}