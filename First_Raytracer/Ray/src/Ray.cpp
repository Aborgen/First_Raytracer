#include "../Ray.h"

namespace Processing
{
	Ray::Ray(Utils::Vec3 origin, Utils::Vec3 direction, Type type) : type(type)
	{
		this->origin = origin;
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

	Utils::Vec3 Ray::getDirection() const
	{
		return direction;
	}

	void Ray::setDirection(float x, float y, float z)
	{
		Utils::Vec3 direction(x, y, z);
		this->direction = direction;
	}
	Ray::Type Ray::getType() const
	{
		return type;
	}
}