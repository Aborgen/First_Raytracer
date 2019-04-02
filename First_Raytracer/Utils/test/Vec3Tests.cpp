#include "catch.hpp"

#include "../Vec3.h"

SCENARIO("Basic operations between two vectors in R^3")
{
	using namespace Utils;
	SECTION("Addition")
	{
		Vec3 expected(3.5f, 2.0f, 1.0f);

		Vec3 first(2.5f, 1.0f, 1.0f);
		Vec3 second(1.0f, 1.0f, 0.0f);
		Vec3 result = first + second;
		REQUIRE(
			(
				expected.getX() == result.getX() &&
				expected.getY() == result.getY() &&
				expected.getZ() == result.getZ()
			)
		);
	}
	
	SECTION("Subtraction")
	{
		Vec3 expected(1.5f, 0.0f, 1.0f);

		Vec3 first(2.5f, 1.0f, 1.0f);
		Vec3 second(1.0f, 1.0f, 0.0f);
		Vec3 result = first - second;
		REQUIRE(
			(
				expected.getX() == result.getX() &&
				expected.getY() == result.getY() &&
				expected.getZ() == result.getZ()
			)
		);
	}

	SECTION("Multiplication")
	{
		Vec3 expected(8.14f, 0.0f, -8.954);

		Vec3 vector(2.0f, 0.0f, -2.2f);
		float scalar = 4.07f;
		Vec3 result = scalar * vector;
		REQUIRE(
			(
				Approx(expected.getX()) == result.getX() &&
				Approx(expected.getY()) == result.getY() &&
				Approx(expected.getZ()) == result.getZ()
			)
		);
	}

	SECTION("Equality")
	{
		Vec3 first(1.5f, 1.0f, 2.0f);
		Vec3 second(1.5f, 1.0f, 2.0f);
		bool objectEquality = first == second;
		REQUIRE(objectEquality);
	}

	SECTION("Inequality")
	{
		Vec3 first(1.0f, 1.0f, 1.0f);
		Vec3 second(1.5f, 1.0f, 2.0f);
		bool objectInequality = first != second;
		REQUIRE(objectInequality);
	}

	SECTION("Length")
	{
		Vec3 vector(2.0f, 4.0f, 6.0f);
		Approx expected(7.4833f);
		REQUIRE(expected == vector.length());
	}
}