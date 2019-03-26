#include "../Coordinates.h"

namespace Utils
{
	Coordinates::Coordinates(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Coordinates::getX()
	{
		return x;
	}

	void Coordinates::setX(float x)
	{
		this->x = x;
	}

	float Coordinates::getY()
	{
		return y;
	}

	void Coordinates::setY(float y)
	{
		this->y = y;
	}

	float Coordinates::getZ()
	{
		return z;
	}

	void Coordinates::setZ(float z)
	{
		this->z = z;
	}
}
