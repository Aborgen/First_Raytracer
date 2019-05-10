#ifndef VECTOR_H
#define VECTOR_H
#pragma once

namespace Utils
{
	template <class T>
	class Vector
	{
	public:
		Vector() {};
		Vector(float x, float y, float z) {};
		Vector(float x, float y, float z, float w) {};
		virtual double length() = 0;
		virtual bool operator==(const T &other) = 0;
		virtual bool operator!=(const T &other) = 0;
		virtual T& operator+=(const T &other) = 0;
		virtual T operator+(const T &other) = 0;
		virtual T& operator-=(const T &other) = 0;
		virtual T operator-(const T &other) = 0;
		float getX() const { return x; }
		void setX(float x) { this->x = x; }
		float getY() const { return y; }
		void setY(float y) { this->y = y; }
		float getZ() const { return z; }
		void setZ(float z) { this->z = z; }
		virtual ~Vector() {}

	protected:
		float x;
		float y;
		float z;
	};
}

#endif // !VECTOR_H