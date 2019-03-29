#include "catch.hpp"

#include "../Mat4.h"

SCENARIO("Basic operations between two 4x4 matrices")
{
	using namespace Utils;

	SECTION("Addition")
	{
		Mat4 first(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Mat4 second(
			0.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 0.0f
		);

		Mat4 expected(
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		);

		Mat4 result = first + second;
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

	SECTION("Subtraction")
	{
		Mat4 first(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Mat4 second(
			0.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 0.0f
		);

		Mat4 expected(
			 1.0f, -1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,  1.0f
		);

		Mat4 result = first - second;
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

	SECTION("Multiplication")
	{
		Mat4 first(
			2.0f, 0.0f, 0.0f, 25.17f,
			0.0f, 2.0f, 0.0f, 1.01f,
			0.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 0.0f
		);
		
		Mat4 second(
			0.0f, 0.0f,  0.0f, -1.0f,
			0.0f, 5.24f, 0.0f, -1.0f,
			0.0f, 0.2f,  0.0f,  0.0f,
			0.0f, 0.0f,  0.0f,  0.0f
		);

		Mat4 expected(
			0.0f, 0.0f,   0.0f, -2.0f,
			0.0f, 10.48f, 0.0f, -2.0f,
			0.0f, 5.44f,  0.0f, -1.0f,
			0.0f, 5.44f,  0.0f, -1.0f
		);

		Mat4 result = first * second;

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

	SECTION("Equality")
	{
		Mat4 first(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Mat4 second(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		bool objectEquality = first == second;
		REQUIRE(objectEquality);
	}
	
	SECTION("Inequality")
	{
		Mat4 first(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Mat4 second(
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		);

		bool objectInequality = first != second;
		REQUIRE(objectInequality);
	}
}