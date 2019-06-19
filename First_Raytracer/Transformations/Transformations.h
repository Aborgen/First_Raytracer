#ifndef TRANSFORMATION_H
#pragma once

#include "../Utils/Mat3.h"
#include "../Utils/Mat4.h"
#include "../Utils/Vec3.h"

namespace Utils
{
	class Transformations
	{
	public:
		static Mat4 translate(float tx, float ty, float tz);
		static Mat3 rotate(float degrees, const Vec3 &axis);
		static Mat4 scale(float sx, float sy, float sz);

	private:
		Transformations() {}
	};
}

#endif // !TRANSFORMATION_H
