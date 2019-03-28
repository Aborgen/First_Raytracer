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

	float Vec4::getW()
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

	Vec4 Vec4::operator+(const Vec4 &other)
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

	Vec4 Vec4::operator-(const Vec4 &other)
	{
		Vec4 temp(*this);
		temp -= other;
		return temp;
	}
}