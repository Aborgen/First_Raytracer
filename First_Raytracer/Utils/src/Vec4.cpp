#include <cmath>

#include "../Vec4.h"

namespace Utils
{
	Vec4::Vec4(float x, float y, float z, float w) : Vector(x, y, z, w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float Vec4::getW() const
	{
		return w;
	}

	void Vec4::setW(float w)
	{
		this->w = w;
	}

	double Vec4::length()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
	}

	bool Vec4::operator==(const Vec4 &other)
	{
		return (
			x == other.x &&
			y == other.y &&
			z == other.z &&
			w == other.w
		);
	}

	bool Vec4::operator!=(const Vec4 &other)
	{
		return !operator==(other);
	}

	Vec4& Vec4::operator+=(const Vec4 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vec4 Vec4::operator+(const Vec4 &other) const
	{
		Vec4 temp(*this);
		temp += other;
		return temp;
	}

	Vec4& Vec4::operator-=(const Vec4 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vec4 Vec4::operator-(const Vec4 &other) const
	{
		Vec4 temp(*this);
		temp -= other;
		return temp;
	}

	Vec4& Vec4::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vec4 Vec4::operator*(float scalar)
	{
		Vec4 temp(*this);
		temp *= scalar;
		return temp;
	}

	Vec4& Vec4::operator*=(int scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vec4 Vec4::operator*(int scalar)
	{
		Vec4 temp(*this);
		temp *= scalar;
		return temp;
	}
}