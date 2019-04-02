#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>

#include "../Operations.h"


namespace Utils
{
	Vec3 Operations::cross(Vec3 &one, Vec3 &two)
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

	float Operations::dot(Vec3 &one, Vec3 &two)
	{
		float sumOfProducts = (
			(one.getX() * two.getX()) +
			(one.getY() * two.getY()) +
			(one.getZ() * two.getZ())
			);

		return sumOfProducts;
	}

	float Operations::dot(Vec4 &one, Vec4 &two)
	{
		float sumOfProducts = (
			(one.getX() * two.getX()) +
			(one.getY() * two.getY()) +
			(one.getZ() * two.getZ()) +
			(one.getW() * two.getW())
			);

		return sumOfProducts;
	}

	Vec3 Operations::normalize(Vec3 &vector)
	{
		double length = vector.length();
		if (length <= 0)
		{
			throw std::exception("A vector with a length of 0 cannot be normalized");
		}

		float normX = (float)(vector.getX() / length);
		float normY = (float)(vector.getY() / length);
		float normZ = (float)(vector.getZ() / length);
		return Vec3(normX, normY, normZ);
	}

	Vec4 Operations::normalize(Vec4 &vector)
	{
		double length = vector.length();
		if (length <= 0)
		{
			throw std::exception("A vector with a length of 0 cannot be normalized");
		}

		float normX = (float)(vector.getX() / length);
		float normY = (float)(vector.getY() / length);
		float normZ = (float)(vector.getZ() / length);
		float normW = (float)(vector.getW() / length);
		return Vec4(normX, normY, normZ, normW);
	}

	float Operations::toRadians(float degrees)
	{
		float halfCircle = (float)(M_PI / 180);
		return degrees * halfCircle;
	}

	Mat3 Operations::transpose(Mat3 matrix)
	{
		float ra0 = matrix[0][0];
		float ra1 = matrix[1][0];
		float ra2 = matrix[2][0];

		float rb0 = matrix[0][1];
		float rb1 = matrix[1][1];
		float rb2 = matrix[2][1];

		float rc0 = matrix[0][2];
		float rc1 = matrix[1][2];
		float rc2 = matrix[2][2];

		return Mat3(
			ra0, ra1, ra2,
			rb0, rb1, rb2,
			rc0, rc1, rc2
		);
	}

	Mat4 Operations::transpose(Mat4 matrix)
	{
		float ra0 = matrix[0][0];
		float ra1 = matrix[1][0];
		float ra2 = matrix[2][0];
		float ra3 = matrix[3][0];

		float rb0 = matrix[0][1];
		float rb1 = matrix[1][1];
		float rb2 = matrix[2][1];
		float rb3 = matrix[3][1];

		float rc0 = matrix[0][2];
		float rc1 = matrix[1][2];
		float rc2 = matrix[2][2];
		float rc3 = matrix[3][2];

		float rd0 = matrix[0][3];
		float rd1 = matrix[1][3];
		float rd2 = matrix[2][3];
		float rd3 = matrix[3][3];

		return Mat4(
			ra0, ra1, ra2, ra3,
			rb0, rb1, rb2, rb3,
			rc0, rc1, rc2, rc3,
			rd0, rd1, rd2, rd3

		);
	}

	Mat3 Operations::outerProduct(Vec3 &one, Vec3 &two)
	{
		float xScalar = one.getX();
		float yScalar = one.getY();
		float zScalar = one.getZ();
		Vec3 rowOne = two * xScalar;
		Vec3 rowTwo = two * yScalar;
		Vec3 rowThree = two * zScalar;
		return Mat3(
			rowOne.getX(),   rowOne.getY(),   rowOne.getZ(),
			rowTwo.getX(),   rowTwo.getY(),   rowTwo.getZ(),
			rowThree.getX(), rowThree.getY(), rowThree.getZ()
		);
	}
}