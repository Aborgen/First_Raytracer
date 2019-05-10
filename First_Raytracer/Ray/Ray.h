#ifndef RAY_H
#define RAY_H
#pragma once

#include "../Utils/Vec3.h"
namespace Processing
{
	class Ray
	{
	public:
		Ray() {};
		Ray(Utils::Vec3 direction, Utils::Vec3 origin);
		Utils::Vec3 getDirection() const;
		void setDirection(float x, float y, float z);
		Utils::Vec3 getOrigin() const;
		void setOrigin(float x, float y, float z);

	private:
		Utils::Vec3 direction;
		Utils::Vec3 origin;
	};
}

#endif // !RAY_H
