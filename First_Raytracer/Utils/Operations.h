#ifndef OPERATIONS_H
#define OPERATIONS_H
#pragma once

#include "Vec3.h"

namespace Utils
{
	class Operations
	{
	public:
		static Vec3 cross(Vec3 &one, Vec3 &two);
		static float dot(Vec3 &one, Vec3 &two);
		static Vec3 normalize(Vec3 &vector);
		static float toRadians(float degrees);

	private:
		Operations() {}
	};
}

#endif // !OPERATIONS_H