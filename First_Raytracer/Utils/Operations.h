#ifndef OPERATIONS_H
#define OPERATIONS_H
#pragma once

#include "Vec3.h"

namespace Utils
{
	class Operations
	{
	public:
		Vec3 cross(const Vec3 &one, const Vec3 &two);
		float dot(const Vec3 &one, const Vec3 &two);
		Vec3 normalize(const Vec3 &vector);
		float toRadians(float degrees);

	private:

	};
}

#endif // !OPERATIONS_H