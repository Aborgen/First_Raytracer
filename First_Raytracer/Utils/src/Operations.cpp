#include <cmath>

#include "../Operations.h"


namespace Utils
{
	Vec3 Operations::cross(const Vec3 &one, const Vec3 &two)
	{
		float oneX = one.getX();
		float oneY = one.getY();
		float oneZ = one.getZ();

		float twoX = two.getX();
		float twoY = two.getY();
		float twoZ = two.getZ();

		float i = (oneY * twoZ) - (oneZ * twoY);
		float j = (oneZ * twoX) - (oneX * twoZ);
		float k = (oneX * twoY) - (oneY * twoX);
		return Vec3(i, j, k);
	}


	float Operations::dot(const Vec3 &one, const Vec3 &two)
	{
		float sumOfProducts = (
			(one.getX() * two.getX()) + 
			(one.getY() * two.getY()) + 
			(one.getZ() * two.getZ())
		);

		return sumOfProducts;
	}

	Vec3 Operations::normalize(const Vec3 &vector)
	{
		int length = vector.length();
		if (length <= 0)
		{
			throw std::exception("A vector with a length of 0 cannot be normalized");
		}

		float normX = vector.getX() / length;
		float normY = vector.getY() / length;
		float normZ = vector.getZ() / length;
		return Vec3(normX, normY, normZ);
	}

	float Operations::toRadians(float degrees)
	{
		float halfCircle = M_PI / 180;
		return degrees * halfCircle;
	}
}