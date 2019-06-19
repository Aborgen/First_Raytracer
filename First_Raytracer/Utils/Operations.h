#ifndef OPERATIONS_H
#define OPERATIONS_H
#pragma once

#include <optional>

#include "Mat3.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Vec4.h"

namespace Utils
{
	class Operations
	{
	public:
		static Vec3 cross(const Vec3 &one, Vec3 &two);
		static float dot(const Vec3 &one, const Vec3 &two);
		static float dot(const Vec4 &one, Vec4 &two);
		static Vec3 normalize(const Vec3 &vector);
		static Vec4 normalize(const Vec4 &vector);
		static float toRadians(float degrees);
		static Mat3 transpose(const Mat3 matrix);
		static Mat4 transpose(const Mat4 matrix);
		static Mat3 outerProduct(const Vec3 &one, Vec3 &two);
		static Vec3 vectorTransform(const Mat4 &matrix, const Vec3 &vector, bool includeTranslation = false);
		static std::optional<Mat4> inverse(const Mat4 &matrix);

	private:
		static bool gaussJordan(Mat4 matrix, Mat4 &inverseMatrix);
		static bool upperTriangle(std::array<float, 4> &pivotRow, Mat4 &matrix, Mat4 &inverseMatrix, size_t pivotIndex = 0);
		static bool lowerTriangle(std::array<float, 4> &pivotRow, Mat4 &matrix, Mat4 &inverseMatrix, size_t pivotIndex = 3);
		Operations() {}
	};
}

#endif // !OPERATIONS_H