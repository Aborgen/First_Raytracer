#include "Sample.h"

namespace Processing
{
	Sample::Sample(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float Sample::getX()
	{
		return x;
	}

	void Sample::setX(float x)
	{
		this->x = x;
	}

	float Sample::getY()
	{
		return y;
	}

	void Sample::setY(float y)
	{
		this->y = y;
	}
}