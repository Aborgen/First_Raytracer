#include "catch.hpp"

#include "../Transformations.h"

SCENARIO("Basic transformations")
{
	using namespace Utils;

	SECTION("Translation")
	{
		float tx = 2.34f;
		float ty = 0.0f;
		float tz = 2.34f;
		Mat4 expected(
			1.0f, 0.0f, 0.0f, 2.34f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 2.34f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Mat4 result = Transformations::translate(tx, ty, tz);
		REQUIRE(
			(
				Approx(expected[0][0]) == result[0][0] &&
				Approx(expected[0][1]) == result[0][1] &&
				Approx(expected[0][2]) == result[0][2] &&
				Approx(expected[0][3]) == result[0][3] &&

				Approx(expected[1][0]) == result[1][0] &&
				Approx(expected[1][1]) == result[1][1] &&
				Approx(expected[1][2]) == result[1][2] &&
				Approx(expected[1][3]) == result[1][3] &&

				Approx(expected[2][0]) == result[2][0] &&
				Approx(expected[2][1]) == result[2][1] &&
				Approx(expected[2][2]) == result[2][2] &&
				Approx(expected[2][3]) == result[2][3] &&

				Approx(expected[3][0]) == result[3][0] &&
				Approx(expected[3][1]) == result[3][1] &&
				Approx(expected[3][2]) == result[3][2] &&
				Approx(expected[3][3]) == result[3][3]
			)
		);
	}

	SECTION("Rotation")
	{
		float degrees = 60.0f;
		Vec3 axis(0.0f, 1.0f, 2.0f);
		Mat3 expected(
			 0.49f, -0.77f, 0.39f,
			 0.77f, 0.6f, 0.2f,
			-0.39f, 0.2f, 0.9f
		);

		Mat3 result = Transformations::rotate(degrees, axis);
		REQUIRE(
			(
				Approx(expected[0][0]).margin(0.01) == result[0][0] &&
				Approx(expected[0][1]).margin(0.01) == result[0][1] &&
				Approx(expected[0][2]).margin(0.01) == result[0][2] &&

				Approx(expected[1][0]).margin(0.01) == result[1][0] &&
				Approx(expected[1][1]).margin(0.01) == result[1][1] &&
				Approx(expected[1][2]).margin(0.01) == result[1][2] &&

				Approx(expected[2][0]).margin(0.01) == result[2][0] &&
				Approx(expected[2][1]).margin(0.01) == result[2][1] &&
				Approx(expected[2][2]).margin(0.01) == result[2][2]
			)
		);
	}

	SECTION("Scale")
	{
		float sx = 5.5f;
		float sy = -25.0f;
		float sz = 0.0f;
		Mat4 expected(
			sx,   0.0f, 0.0f, 0.0f,
			0.0f, sy,   0.0f, 0.0f,
			0.0f, 0.0f, sz,   0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Mat4 result = Transformations::scale(sx, sy, sz);
		REQUIRE(
			(
				Approx(expected[0][0]) == result[0][0] &&
				Approx(expected[0][1]) == result[0][1] &&
				Approx(expected[0][2]) == result[0][2] &&
				Approx(expected[0][3]) == result[0][3] &&

				Approx(expected[1][0]) == result[1][0] &&
				Approx(expected[1][1]) == result[1][1] &&
				Approx(expected[1][2]) == result[1][2] &&
				Approx(expected[1][3]) == result[1][3] &&

				Approx(expected[2][0]) == result[2][0] &&
				Approx(expected[2][1]) == result[2][1] &&
				Approx(expected[2][2]) == result[2][2] &&
				Approx(expected[2][3]) == result[2][3] &&

				Approx(expected[3][0]) == result[3][0] &&
				Approx(expected[3][1]) == result[3][1] &&
				Approx(expected[3][2]) == result[3][2] &&
				Approx(expected[3][3]) == result[3][3]
			)
		);
	}
}