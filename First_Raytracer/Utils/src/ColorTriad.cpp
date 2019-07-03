#include <algorithm>

#include "../ColorTriad.h"

namespace Utils
{
	ColorTriad::ColorTriad(float r, float g, float b)
	{
		setR(r);
		setG(g);
		setB(b);
	}

	float ColorTriad::getR()
	{
		return r;
	}

	unsigned char ColorTriad::getRByte()
	{
		return toByte(r);
	}

	void ColorTriad::setR(float r)
	{
		this->r = clamp(r);
	}

	float ColorTriad::getG()
	{
		return g;
	}

	unsigned char ColorTriad::getGByte()
	{
		return toByte(g);
	}

	void ColorTriad::setG(float g)
	{
		this->g = clamp(g);
	}

	float ColorTriad::getB()
	{
		return b;
	}

	unsigned char ColorTriad::getBByte()
	{
		return toByte(b);
	}

	void ColorTriad::setB(float b)
	{
		this->b = clamp(b);
	}

	ColorTriad& ColorTriad::operator*=(const ColorTriad &other)
	{
		setR(r * other.r);
		setG(g * other.g);
		setB(b * other.b);
		return *this;
	}

	ColorTriad ColorTriad::operator*(const ColorTriad &other)
	{
		ColorTriad temp(*this);
		temp *= other;
		return temp;
	}

	ColorTriad& ColorTriad::operator*=(float scalar)
	{
		setR(r * scalar);
		setG(g * scalar);
		setB(b * scalar);
		return *this;
	}

	ColorTriad ColorTriad::operator*(float scalar)
	{
		ColorTriad temp(*this);
		temp *= scalar;
		return temp;
	}

	ColorTriad& ColorTriad::operator+=(const ColorTriad &other)
	{
		setR(r + other.r);
		setG(g + other.g);
		setB(b + other.b);
		return *this;
	}

	ColorTriad ColorTriad::operator+(const ColorTriad &other)
	{
		ColorTriad temp(*this);
		temp += other;
		return temp;
	}

	float ColorTriad::normalize(float value)
	{
		if (value <= 1.0f) {
			return value;
		}

		return value / MAX;
	}

	float ColorTriad::clamp(float value)
	{
		return std::max(std::min(value, MAX), 0.0f);
	}

	unsigned char ColorTriad::toByte(float value)
	{
		value = normalize(value);
		if (value >= 1.0) {
			return 255;
		}
		else if (value <= 0) {
			return 0;
		}

		return static_cast<unsigned char>(std::max(value, MIN) * 255.0f + 0.5f);
	}
}