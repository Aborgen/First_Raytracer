#ifndef COORDINATES_H
#define COORDINATES_H
#pragma once

namespace Utils
{
	class Coordinates
	{
	public:
		Coordinates(float x, float y, float z);
		float getX();
		void setX(float x);
		float getY();
		void setY(float y);
		float getZ();
		void setZ(float z);

	protected:
		float x;
		float y;
		float z;
	};
}

#endif // !COORDINATES_H