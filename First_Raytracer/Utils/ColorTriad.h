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
		int getR();
		unsigned char getRByte();
		void setR(float r);
		int getG();
		unsigned char getGByte();
		void setG(float g);
		int getB();
		unsigned char getBByte();
		void setB(float b);
		ColorTriad& operator*=(const ColorTriad &other);
		ColorTriad operator*(const ColorTriad &other);
		ColorTriad& operator*=(float scalar);
		ColorTriad operator*(float scalar);
		ColorTriad& operator+=(const ColorTriad &other);
		ColorTriad operator+(const ColorTriad &other);

	private:
		int MIN{ 0 };
		int MAX{ 255 };
		float normalize(int value);
		int quantize(float value);
		float clamp(float value);
		unsigned char toByte(int value);
		int r{ MIN };
		int g{ MIN };
		int b{ MIN };
	};
}

#endif // !COLORTRIAD_H
