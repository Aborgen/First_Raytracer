#include "../DirectionalLight.h"

namespace Processing
{
	Utils::Vec3 DirectionalLight::getDirection()
	{
		return getCoordinates();
	}

	void DirectionalLight::setDirection(float x, float y, float z)
	{
		setCoordinates(x, y, z);
	}
}