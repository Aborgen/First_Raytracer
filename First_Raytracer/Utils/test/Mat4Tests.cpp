#include "catch.hpp"

#include "../Mat4.h"
#include "../Vec4.h"

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
			5.0f, 2.0f, 0.25f, 1.0f,
			0.0f, 1.0f, 3.0f,  4.0f,
			0.0f, 0.0f, 1.0f,  1.0f, 
			7.0f, 7.0f, 7.0f,  7.0f
		);
		
		Mat4 second(
			1.0f,  2.0f,  3.0f,  4.0f,
			5.0f,  6.0f,  7.0f,  8.0f,
			9.0f,  10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f
		);

		Mat4 expected(
			30.25f, 38.5f,  46.75f, 55.0f,
			84.0f,  92.0f,  100.0f, 108.0f,
			22.0f,  24.0f,  26.0f,  28.0f,
			196.0f, 224.0f, 252.0f, 280.0f
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

SCENARIO("Basic operations between a 4x4 matrix and a vector in R^4")
{
	using namespace Utils;

	SECTION("Multiplication")
	{
		Vec4 expected(1.0f, 3.25f, 2.0f, 0.75f);

		Mat4 matrix(
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 2.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, -1.0f, 0.0f, 1.0f
		);

		Vec4 vector(-1.0f, 1.25f, 0.0f, 2.0f);
		Vec4 result = matrix * vector;

		bool objectEquality = expected == result;
		REQUIRE(objectEquality);
	}
}