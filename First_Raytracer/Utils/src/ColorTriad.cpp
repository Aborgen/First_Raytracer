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

	void ColorTriad::setR(float r)
	{
		this->r = normalize(r);
	}

	float ColorTriad::getG()
	{
		return g;
	}

	void ColorTriad::setG(float g)
	{
		this->g = normalize(g);
	}

	float ColorTriad::getB()
	{
		return b;
	}

	void ColorTriad::setB(float b)
	{
		this->b = normalize(b);
	}

	float ColorTriad::normalize(float value)
	{
		return value - MIN / MAX - MIN;
	}
}