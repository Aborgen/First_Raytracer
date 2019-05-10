#include "../Ray.h"

namespace Processing
{
	Ray::Ray(Utils::Vec3 direction, Utils::Vec3 origin)
	{
		this->direction = direction;
		this->origin = origin;
	}

	Utils::Vec3 Ray::getDirection() const
	{
		return direction;
	}

	void Ray::setDirection(float x, float y, float z)
	{
		Utils::Vec3 direction(x, y, z);
		this->direction = direction;
	}

	Utils::Vec3 Ray::getOrigin() const
	{
		return origin;
	}

	void Ray::setOrigin(float x, float y, float z)
	{
		Utils::Vec3 origin(x, y, z);
		this->origin = origin;
	}
}