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

	int ColorTriad::getR()
	{
		return r;
	}

	unsigned char ColorTriad::getRByte()
	{
		return toByte(r);
	}

	void ColorTriad::setR(float r)
	{
		this->r = quantize(clamp(r));
	}

	int ColorTriad::getG()
	{
		return g;
	}

	unsigned char ColorTriad::getGByte()
	{
		return toByte(g);
	}

	void ColorTriad::setG(float g)
	{
		this->g = quantize(clamp(g));
	}

	int ColorTriad::getB()
	{
		return b;
	}

	unsigned char ColorTriad::getBByte()
	{
		return toByte(b);
	}

	void ColorTriad::setB(float b)
	{
		this->b = quantize(clamp(b));
	}

	ColorTriad& ColorTriad::operator*=(const ColorTriad &other)
	{
		setR(normalize(r) * normalize(other.r));
		setG(normalize(g) * normalize(other.g));
		setB(normalize(b) * normalize(other.b));
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
		setR(normalize(r) * scalar);
		setG(normalize(g) * scalar);
		setB(normalize(b) * scalar);
		return *this;
	}

	ColorTriad ColorTriad::operator*(float scalar)
	{
		ColorTriad temp(*this);
		temp *= scalar;
		return temp;
	}

	ColorTriad& ColorTriad::operator/=(float scalar)
	{
		setR(normalize(r) / scalar);
		setG(normalize(g) / scalar);
		setB(normalize(b) / scalar);
		return *this;
	}

	ColorTriad ColorTriad::operator/(float scalar) const
	{
		ColorTriad temp(*this);
		temp /= scalar;
		return temp;
	}

	ColorTriad& ColorTriad::operator+=(const ColorTriad &other)
	{
		setR(normalize(r) + normalize(other.r));
		setG(normalize(g) + normalize(other.g));
		setB(normalize(b) + normalize(other.b));
		return *this;
	}

	ColorTriad ColorTriad::operator+(const ColorTriad &other)
	{
		ColorTriad temp(*this);
		temp += other;
		return temp;
	}

	bool ColorTriad::operator==(const ColorTriad &other)
	{
		return (
			r == other.r &&
			g == other.g &&
			b == other.b
		);
	}

	float ColorTriad::normalize(int value)
	{
		return (float)value / MAX;
	}

	int ColorTriad::quantize(float value)
	{
		int valueI = static_cast<int>(value * 256.0f);
		if (valueI == 256) {
			return 255;
		}

		return valueI;
	}

	float ColorTriad::clamp(float value)
	{
		return std::max(std::min(value, 1.0f), 0.0f);
	}

	unsigned char ColorTriad::toByte(int value)
	{
		return static_cast<unsigned char>(value);
	}
}