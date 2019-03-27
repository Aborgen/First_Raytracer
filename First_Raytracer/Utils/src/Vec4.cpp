#include "../Vec4.h"

namespace Utils
{
	Vec4::Vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vec4::getW()
	{
		return w;
	}

	Vec4::setW(float w)
	{
		this->w = w;
	}

	int Vec4::length()
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->z, 2));
	}

	Vec4::operator==(const Vec4 &other)
	{
		return (
			this->x == other->getX() &&
			this->y == other->getY() &&
			this->z == other->getZ() &&
			this->w == other->getW() &&
			);
	}

	Vec4::operator!=(const Vec4 &other)
	{
		return !operator==(other);
	}

	Vec4::operator+(const Vec4 &other)
	{
		Vec4 sum(
			this->x + other->getX(),
			this->y + other->getY(),
			this->z + other->getZ(),
			this->w + other->getW()
		);

		return sum;
	}

	Vec4::operator-(const Vec4 &other)
	{
		Vec4 difference(
			this->x - other->getX(),
			this->y - other->getY(),
			this->z - other->getZ(),
			this->w - other->getW()
		);

		return difference;
	}
}