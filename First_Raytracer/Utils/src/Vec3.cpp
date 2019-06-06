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

	double Vec3::length()
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}

	Vec3& Vec3::reverse()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
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

	Vec3 Vec3::operator+(const Vec3 &other) const
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

	Vec3 Vec3::operator-(const Vec3 &other) const
	{
		Vec3 temp(*this);
		temp -= other;
		return temp;
	}

	Vec3& Vec3::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	Vec3 Vec3::operator*(float scalar) const
	{
		Vec3 temp(*this);
		temp *= scalar;
		return temp;
	}

	Vec3 operator*(float scalar, const Vec3 &vector)
	{
		return vector * scalar;
	}
}