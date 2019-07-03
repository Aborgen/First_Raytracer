#include "../Ray.h"

#include "../Utils/Operations.h"

namespace Processing
{
	Ray::Ray(Utils::Vec3 origin, Utils::Vec3 direction, Type type) : type(type)
	{
		this->origin = origin;
		setDirection(direction);
	}

	Utils::Vec3 Ray::specificPoint(float t) const
	{
		return origin + t * direction;
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
		setDirection(direction);
	}

	void Ray::setDirection(const Utils::Vec3 &direction)
	{
		this->direction = Utils::Operations::normalize(direction);
	}

	Ray::Type Ray::getType() const
	{
		return type;
	}
}