#ifndef VEC4_H
#define VEC4_H
#pragma once

#include "Vector.h"

namespace Utils
{
	class Vec4 : public Vector<Vec4>
	{
	public:
		Vec4(float x, float y, float z, float w);
		float getW();
		void setW(float w);
		double length();
		bool operator==(const Vec4 &other);
		bool operator!=(const Vec4 &other);
		Vec4& operator+=(const Vec4 &other);
		Vec4 operator+(const Vec4 &other);
		Vec4& operator-=(const Vec4 &other);
		Vec4 operator-(const Vec4 &other);

	private:
		float w;
	};
}

#endif // !VEC4_H