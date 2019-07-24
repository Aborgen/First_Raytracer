#include "catch.hpp"

#include "../Vec4.h"

SCENARIO("Basic operations between two vectors in R^4")
{
	using namespace Utils;
	SECTION("Addition")
	{
		Vec4 expected(3.5f, 2.0f, 1.0f, 10.0f);

		Vec4 first(2.5f, 1.0f, 1.0f, 7.5f);
		Vec4 second(1.0f, 1.0f, 0.0f, 2.5f);
		Vec4 result = first + second;
		REQUIRE(
			(
				expected.getX() == result.getX() &&
				expected.getY() == result.getY() &&
				expected.getZ() == result.getZ() &&
				expected.getW() == result.getW() 
			)
		);
	}
	
	SECTION("Subtraction")
	{
		Vec4 expected(1.5f, 0.0f, 1.0f, 3.5);

		Vec4 first(2.5f, 1.0f, 1.0f, 4.0f);
		Vec4 second(1.0f, 1.0f, 0.0f, 0.5f);
		Vec4 result = first - second;
		REQUIRE(
			(
				expected.getX() == result.getX() &&
				expected.getY() == result.getY() &&
				expected.getZ() == result.getZ() &&
				expected.getW() == result.getW()
			)
		);
	}

	SECTION("Equality")
	{
		Vec4 first(1.5f, 1.0f, 2.0f, 0.0f);
		Vec4 second(1.5f, 1.0f, 2.0f, 0.0f);
		bool objectEquality = first == second;
		REQUIRE(objectEquality);
	}

	SECTION("Inequality")
	{
		Vec4 first(1.0f, 1.0f, 1.0f, 1.0f);
		Vec4 second(1.5f, 1.0f, 2.0f, 0.0f);
		bool objectInequality = first != second;
		REQUIRE(objectInequality);
	}

	SECTION("Length")
	{
		Vec4 vector(2.0f, 4.0f, 6.0f, 8.0f);
		Approx expected(10.9545f);
		REQUIRE(expected == vector.length());
	}
}

SCENARIO("Interactions between a vector in R^4 and a scalar")
{
	using namespace Utils;
	SECTION("Multiplication (float)")
	{
		Vec4 expected(10.0f, 5.0f, 0.0f, 5.0f);

		Vec4 first(2.0f, 1.0f, 0.0f, 1.0f);
		float scalar = 5.0f;
		Vec4 result = first * scalar;
		REQUIRE(
			(
				expected.getX() == result.getX() &&
				expected.getY() == result.getY() &&
				expected.getZ() == result.getZ() &&
				expected.getW() == result.getW()
			)
		);
	}	
	
	SECTION("Multiplication (int)")
	{
		Vec4 expected(10.0f, 5.0f, 0.0f, 5.0f);

		Vec4 first(2.0f, 1.0f, 0.0f, 1.0f);
		int scalar = 5;
		Vec4 result = first * scalar;
		REQUIRE(
			(
				expected.getX() == result.getX() &&
				expected.getY() == result.getY() &&
				expected.getZ() == result.getZ() &&
				expected.getW() == result.getW()
			)
		);
	}
}