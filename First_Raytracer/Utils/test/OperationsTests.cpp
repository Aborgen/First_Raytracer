#include <optional>

#include "catch.hpp"

#include "../Operations.h"
#include "../Vec3.h"
#include "../Vec4.h"

SCENARIO("When vectors given are acceptable (in R^3)")
{
	using namespace Utils;
	SECTION("Cross product between two vectors")
	{
		Vec3 first(1.0f, 2.0f, 3.0f);
		Vec3 second(4.0f, 5.0f, 6.0f);

		Vec3 expected(-3.0f, 6.0f, -3.0f);
		Vec3 result = Operations::cross(first, second);
		bool objectEquality = expected == result;
		REQUIRE(objectEquality);
	}

	SECTION("Dot product between two vectors")
	{
		Vec3 first(1.0f, 2.0f, 3.0f);
		Vec3 second(4.0f, 5.0f, 6.0f);

		Approx expected(32);
		float result = Operations::dot(first, second);
		REQUIRE(expected == result);
	}

	SECTION("Normalization of a vector")
	{
		Vec3 vector(2.0f, 4.0f, 6.0f);
		Approx expected(1.0f);
		Vec3 result = Operations::normalize(vector);
		REQUIRE(expected == result.length());
	}

	SECTION("Convert from degrees to radians")
	{
		float degrees = 60.0f;
		Approx expected(1.0472f);
		float result = Operations::toRadians(degrees);
		REQUIRE(expected == result);
	}

	SECTION("Outer product")
	{
		Vec3 first(2.2f, 4.4f, 6.6f);
		Vec3 second(8.8f, 10.1f, 12.12f);
		Mat3 expected(
			19.36f, 22.22f, 26.664f,
			38.72f, 44.44f, 53.328f,
			58.08f, 66.66f, 79.992f
		);

		Mat3 result = Operations::outerProduct(first, second);
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
}

SCENARIO("When vectors given are acceptable (in R^4)")
{
	using namespace Utils;

	SECTION("Dot product between two vectors")
	{
		Vec4 first(1.0f, 2.0f, 3.0f, 4.0f);
		Vec4 second(5.0f, 6.0f, 7.0f, 8.0f);

		Approx expected(70);
		float result = Operations::dot(first, second);
		REQUIRE(expected == result);
	}

	SECTION("Normalization of a vector")
	{
		Vec4 vector(2.0f, 4.0f, 6.0f, 8.0f);
		Approx expected(1.0f);
		Vec4 result = Operations::normalize(vector);
		REQUIRE(expected == result.length());
	}
}

SCENARIO("Operations on a 3x3 matrix")
{
	using namespace Utils;
	SECTION("Transposition")
	{
		Mat3 matrix(
			5.0f, 4.0f, 3.0f,
			6.0f, 3.0f, 2.0f,
			7.0f, 2.0f, 1.0f
		);

		Mat3 expected(
			5.0f, 6.0f, 7.0f,
			4.0f, 3.0f, 2.0f,
			3.0f, 2.0f, 1.0f
		);

		Mat3 result = Operations::transpose(matrix);
		bool objectEquality = expected == result;
		REQUIRE(objectEquality);
	}
}

SCENARIO("Operations on a 4x4 matrix")
{
	using namespace Utils;
	SECTION("Transposition")
	{
		Mat4 matrix(
			5.0f, 4.0f, 3.0f, 2.0f,
			6.0f, 3.0f, 2.0f, 1.0f,
			7.0f, 2.0f, 1.0f, 0.0f,
			8.0f, 1.0f, 0.0f, -1.0f
		);

		Mat4 expected(
			5.0f, 6.0f, 7.0f,  8.0f,
			4.0f, 3.0f, 2.0f,  1.0f,
			3.0f, 2.0f, 1.0f,  0.0f,
			2.0f, 1.0f, 0.0f, -1.0f
		);

		Mat4 result = Operations::transpose(matrix);
		bool objectEquality = expected == result;
		REQUIRE(objectEquality);
	}

	SECTION("Inversion")
	{
		Mat4 matrix(
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 2.0f, 1.0f, 2.0f,
			2.0f, 1.0f, 0.0f, 1.0f,
			2.0f, 0.0f, 1.0f, 4.0f
		);

		Mat4 expected(
			-2.0f, -0.5f,  1.0f,  0.5f,
			 1.0f,  0.5f,  0.0f, -0.5f,
			-8.0f, -1.0f,  2.0f,  2.0f,
			 3.0f,  0.5f, -1.0f, -0.5f
		);

		std::optional<Mat4> result = Operations::inverse(matrix);
		REQUIRE(result.has_value());
		bool objectEquality = expected == result.value();
		REQUIRE(objectEquality);
	}
}