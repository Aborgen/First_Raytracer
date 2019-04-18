#ifndef MAT3_H
#define MAT3_H
#pragma once

#include <array>

#include "Matrix.h"

namespace Utils
{
	class Mat3 : Matrix<Mat3, std::array<float, 3>>
	{
	public:
		Mat3() {};
		Mat3(
			float ra0, float ra1, float ra2,
			float rb0, float rb1, float rb2,
			float rc0, float rc1, float rc2
		);

		bool operator==(const Mat3 &other);
		bool operator!=(const Mat3 &other);
		Mat3& operator+=(const Mat3 &other);
		Mat3 operator+(const Mat3 &other);
		Mat3& operator-=(const Mat3 &other);
		Mat3 operator-(const Mat3 &other);
		Mat3& operator*=(const Mat3 &other);
		Mat3 operator*(const Mat3 &other);
		Mat3& operator*=(float scalar);
		Mat3 operator*(float scalar) const;
		std::array<float, 3>& operator[](int idx);
		std::array<float, 3> operator[](int idx) const;

	private:
		std::array<std::array<float, 3>, 3> data;
	};

	Mat3 operator*(float scalar, const Mat3 &matrix);
}


#endif // !MAT3_H
