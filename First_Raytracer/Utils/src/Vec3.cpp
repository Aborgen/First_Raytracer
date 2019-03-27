#include <cmath>

#include "../Vec3.h"

namespace Utils
{
	Vec3::Vec3(float x, float y, float z) : Vector(x, y, z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	int Vec3::length()
	{
		return (int) sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}

	bool Vec3::operator==(const Vec3 &other)
	{
		return (
			x == other.x &&
			y == other.y &&
			z == other.z
		);
	}

	bool Vec3::operator!=(const Vec3 &other)
	{
		return !operator==(other);
	}

	Vec3& Vec3::operator+=(const Vec3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	
	Vec3 Vec3::operator+(const Vec3 &other)
	{
		Vec3 temp(*this);
		temp += other;
		return temp;
	}

	Vec3& Vec3::operator-=(const Vec3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3 Vec3::operator-(const Vec3 &other)
	{
		Vec3 temp(*this);
		temp -= other;
		return temp;
	}
}