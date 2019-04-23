#ifndef MAT4_H
#define MAT4_H
#pragma once

#include <array>

#include "Matrix.h"

namespace Utils
{
	class Mat4 : public Matrix<Mat4, std::array<float, 4>>
	{
	public:
		Mat4() {};
		Mat4(
			float ra0, float ra1, float ra2, float ra3,
			float rb0, float rb1, float rb2, float rb3,
			float rc0, float rc1, float rc2, float rc3,
			float rd0, float rd1, float rd2, float rd3
		);

		bool operator==(const Mat4 &other);
		bool operator!=(const Mat4 &other);
		Mat4& operator+=(const Mat4 &other);
		Mat4 operator+(const Mat4 &other);
		Mat4& operator-=(const Mat4 &other);
		Mat4 operator-(const Mat4 &other);
		Mat4& operator*=(const Mat4 &other);
		Mat4 operator*(const Mat4 &other);
		Vec4 operator*(Vec4 &vector);
		std::array<float, 4>& operator[](int idx);
		std::array<float, 4> operator[](int idx) const;

	private:
		std::array<std::array<float, 4>, 4> data;
	};
}

#endif // !MAT4_H
