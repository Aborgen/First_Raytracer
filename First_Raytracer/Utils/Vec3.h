#ifndef VEC3_H
#define VEC3_H
#pragma once

#include "Vector.h"

namespace Utils
{
	class Vec3 : public Vector<Vec3>
	{
	public:
		Vec3(float x, float y, float z);
		double length();
		bool operator==(const Vec3 &other);
		bool operator!=(const Vec3 &other);
		Vec3& operator+=(const Vec3 &other);
		Vec3 operator+(const Vec3 &other);
		Vec3& operator-=(const Vec3 &other);
		Vec3 operator-(const Vec3 &other);
	};
}

#endif // !VEC3_H