#ifndef OPERATIONS_H
#define OPERATIONS_H
#pragma once

#include "Mat3.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Vec4.h"

namespace Utils
{
	class Operations
	{
	public:
		static Vec3 cross(Vec3 &one, Vec3 &two);
		static float dot(Vec3 &one, Vec3 &two);
		static float dot(Vec4 &one, Vec4 &two);
		static Vec3 normalize(Vec3 &vector);
		static Vec4 normalize(Vec4 &vector);
		static float toRadians(float degrees);
		static Mat3 transpose(Mat3 matrix);
		static Mat4 transpose(Mat4 matrix);
		static Mat3 outerProduct(Vec3 &one, Vec3 &two);

	private:
		Operations() {}
	};
}

#endif // !OPERATIONS_H