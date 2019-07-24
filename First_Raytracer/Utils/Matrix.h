#ifndef MATRIX_H
#define MATRIX_H
#pragma once

namespace Utils
{
	template <class T, class A>
	class Matrix
	{
	public:
		Matrix() {};
		Matrix(
			float ra0, float ra1, float ra2,
			float rb0, float rb1, float rb2,
			float rc0, float rc1, float rc2
		) {};

		Matrix(
			float ra0, float ra1, float ra2, float ra3,
			float rb0, float rb1, float rb2, float rb3,
			float rc0, float rc1, float rc2, float rc3,
			float rd0, float rd1, float rd2, float rd3
		) {};

		virtual bool operator==(const T &other) = 0;
		virtual bool operator!=(const T &other) = 0;
		virtual T& operator+=(const T &other) = 0;
		virtual T operator+(const T &other) = 0;
		virtual T& operator-=(const T &other) = 0;
		virtual T operator-(const T &other) = 0;
		virtual T& operator*=(const T &other) = 0;
		virtual T operator*(const T &other) = 0;
		virtual A& operator[](int idx) = 0;
		virtual A operator[](int idx) const = 0;
		virtual ~Matrix() {};

	private:

	};
}

#endif // !MATRIX_H
