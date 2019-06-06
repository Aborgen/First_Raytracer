#ifndef COLORTRIAD_H
#define COLORTRIAD_H
#pragma once

namespace Utils
{
	class ColorTriad
	{
	public:
		ColorTriad() {};
		ColorTriad(float r, float g, float b);
		float getR();
		void setR(float r);
		float getG();
		void setG(float g);
		float getB();
		void setB(float b);
		ColorTriad& operator*=(const ColorTriad &other);
		ColorTriad operator*(const ColorTriad &other);
		ColorTriad& operator*=(float scalar);
		ColorTriad operator*(float scalar);
		ColorTriad& operator+=(const ColorTriad &other);
		ColorTriad operator+(const ColorTriad &other);

	private:
		float MIN{ 0.0f };
		float MAX{ 1.0f };
		float normalize(float value);
		float r{ MIN };
		float g{ MIN };
		float b{ MIN };
	};
}

#endif // !COLORTRIAD_H
