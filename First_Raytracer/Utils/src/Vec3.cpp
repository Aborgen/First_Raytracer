#include <cmath>

#include "../Vec3.h"

namespace Utils
{
	int Vec3::length()
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}

	Vec3::operator==(const Vec3 &other)
	{
		return (
			this->x == other->getX() &&
			this->y == other->getY() &&
			this->z == other->getZ()
		);
	}

	Vec3::operator!=(const Vec3 &other)
	{
		return !operator==(other);
	}

	Vec3::operator+(const Vec3 &other)
	{
		Vec3 sum(
			this->x + other->getX(),
			this->y + other->getY(),
			this->z + other->getZ()
		);

		return sum;
	}

	Vec3::operator-(const Vec3 &other)
	{
		Vec3 difference(
			this->x - other->getX(),
			this->y - other->getY(),
			this->z - other->getZ()
		);

		return difference;
	}
}