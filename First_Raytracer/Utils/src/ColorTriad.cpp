#include "../ColorTriad.h"

namespace Utils
{
	ColorTriad::ColorTriad(float r, float g, float b)
	{
		this->r = r;
		this->b = b;
		this->g = g;
	}

	float ColorTriad::getR()
	{
		return r;
	}

	void ColorTriad::setR(float r)
	{
		this->r = r;
	}

	float ColorTriad::getG()
	{
		return g;
	}

	void ColorTriad::setG(float g)
	{
		this->g = g;
	}

	float ColorTriad::getB()
	{
		return b;
	}

	void ColorTriad::setB(float b)
	{
		this->b = b;
	}
}