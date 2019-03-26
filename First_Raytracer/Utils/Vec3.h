#ifndef VEC3_H
#define VEC3_H
#pragma once

#include "Coordinates.h"

namespace Utils
{
	class Vec3 : public Coordinates
	{
	public:
		using Coordinates::Coordinates;
		int length();
		bool operator==(const Vec3 &other);
		bool operator!=(const Vec3 &other);
		bool operator+(const Vec3 &other);
		bool operator-(const Vec3 &other);
	}
}

#endif // !VEC3_H