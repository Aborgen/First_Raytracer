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
		unsigned char getRByte();
		void setR(float r);
		float getG();
		unsigned char getGByte();
		void setG(float g);
		float getB();
		unsigned char getBByte();
		void setB(float b);
		ColorTriad& operator*=(const ColorTriad &other);
		ColorTriad operator*(const ColorTriad &other);
		ColorTriad& operator*=(float scalar);
		ColorTriad operator*(float scalar);
		ColorTriad& operator+=(const ColorTriad &other);
		ColorTriad operator+(const ColorTriad &other);

	private:
		float MIN{ 0.01f };
		float MAX{ 100.0f };
		float normalize(float value);
		float clamp(float value);
		unsigned char toByte(float value);
		float r{ 0.0f };
		float g{ 0.0f };
		float b{ 0.0f };
	};
}

#endif // !COLORTRIAD_H
