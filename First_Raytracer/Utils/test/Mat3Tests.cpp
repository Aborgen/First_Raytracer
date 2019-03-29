#include "catch.hpp"

#include "../Mat3.h"

SCENARIO("Basic operations between two 3x3 matrices")
{
	using namespace Utils;

	SECTION("Addition")
	{
		Mat3 first(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);

		Mat3 second(
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f
		);

		Mat3 expected(
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f
		);

		Mat3 result = first + second;
		REQUIRE(
			(
				Approx(expected[0][0]) == result[0][0] &&
				Approx(expected[0][1]) == result[0][1] &&
				Approx(expected[0][2]) == result[0][2] &&

				Approx(expected[1][0]) == result[1][0] &&
				Approx(expected[1][1]) == result[1][1] &&
				Approx(expected[1][2]) == result[1][2] &&

				Approx(expected[2][0]) == result[2][0] &&
				Approx(expected[2][1]) == result[2][1] &&
				Approx(expected[2][2]) == result[2][2]
			)
		);
	}

	SECTION("Subtraction")
	{
		Mat3 first(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);

		Mat3 second(
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f
		);

		Mat3 expected(
			 1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f
		);

		Mat3 result = first - second;
		REQUIRE(
			(
				Approx(expected[0][0]) == result[0][0] &&
				Approx(expected[0][1]) == result[0][1] &&
				Approx(expected[0][2]) == result[0][2] &&

				Approx(expected[1][0]) == result[1][0] &&
				Approx(expected[1][1]) == result[1][1] &&
				Approx(expected[1][2]) == result[1][2] &&

				Approx(expected[2][0]) == result[2][0] &&
				Approx(expected[2][1]) == result[2][1] &&
				Approx(expected[2][2]) == result[2][2]
			)
		);
	}

	SECTION("Multiplication")
	{
		Mat3 first(
			2.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f,
			0.0f, 1.0f, 1.0f
		);
		
		Mat3 second(
			0.0f, 0.0f,  0.0f,
			0.0f, 5.24f, 0.0f,
			0.0f, 0.2f,  0.0f
		);

		Mat3 expected(
			0.0f, 0.0f,   0.0f,
			0.0f, 10.48f, 0.0f,
			0.0f, 5.44f,  0.0f
		);

		Mat3 result = first * second;

		REQUIRE(
			(
				Approx(expected[0][0]) == result[0][0] &&
				Approx(expected[0][1]) == result[0][1] &&
				Approx(expected[0][2]) == result[0][2] &&

				Approx(expected[1][0]) == result[1][0] &&
				Approx(expected[1][1]) == result[1][1] &&
				Approx(expected[1][2]) == result[1][2] &&

				Approx(expected[2][0]) == result[2][0] &&
				Approx(expected[2][1]) == result[2][1] &&
				Approx(expected[2][2]) == result[2][2]
			)
		);
	}

	SECTION("Equality")
	{
		Mat3 first(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);

		Mat3 second(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);

		bool objectEquality = first == second;
		REQUIRE(objectEquality);
	}
	
	SECTION("Inequality")
	{
		Mat3 first(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);

		Mat3 second(
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		);

		bool objectInequality = first != second;
		REQUIRE(objectInequality);
	}
}