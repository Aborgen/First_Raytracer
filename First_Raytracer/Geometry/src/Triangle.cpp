#include <exception>

#include "../Triangle.h"
#include "../../Utils/Operations.h"

namespace Geometry
{
	Triangle::Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c, const Processing::MaterialProps &material) : Shape(Type::TRIANGLE)
	{
		if (a == b || a == c || b == c)
		{
			throw new std::exception("A triangle is made up of three distinct vertices");
		}

		this->a = a;
		this->b = b;
		this->c = c;
		this->material = material;
	}

	Utils::Vec3 Triangle::getA()
	{
		return a;
	}

	Utils::Vec3 Triangle::getB()
	{
		return b;
	}

	Utils::Vec3 Triangle::getC()
	{
		return c;
	}

	Utils::Vec3 Triangle::getEdge0()
	{
		return b - a;
	}

	Utils::Vec3 Triangle::getEdge1()
	{
		return c - a;
	}

	Utils::Vec3 Triangle::getEdge2()
	{
		return c - b;
	}

	Utils::Vec3 Triangle::getNormal()
	{
		using namespace Utils;
		Vec3 edge0 = getEdge0();
		Vec3 edge1 = getEdge1();
		Vec3 normal = Operations::cross(edge0, edge1);
		return normal;
	}

	std::optional<float> Triangle::intersect(const Processing::Ray &ray)
	{
		using namespace Utils;
		Vec3 direction = ray.getDirection();
		Vec3 edge0 = getEdge0();
		Vec3 edge1 = getEdge1();
		Vec3 P = Operations::cross(direction, edge1);
		float determinant = Operations::dot(edge0, P);
		// A determinant that is close to 0 indicates that it does not intersect.
		// Also catches back-facing triangles, as those will have a negative determinant.
		if (determinant < std::numeric_limits<float>::epsilon()) {
			return std::nullopt;
		}

		float invertedDeterminant = 1 / determinant;

		Vec3 triangleToOrigin = ray.getOrigin() - getA();
		float u = invertedDeterminant * Operations::dot(triangleToOrigin, P);
		if (u < 0 || u > 1) {
			return std::nullopt;
		}

		Vec3 q = Operations::cross(triangleToOrigin, edge0);
		float v = invertedDeterminant * Operations::dot(direction, q);
		if (v < 0 || u + v > 1) {
			return std::nullopt;
		}

		float t = invertedDeterminant * Operations::dot(edge1, q);
		return t;
	}

	Utils::Vec3 Triangle::normalAtPoint(const Utils::Vec3 &point)
	{
		return getNormal();
	}
}