#include <exception>

#include "../Triangle.h"
#include "../../Utils/Operations.h"

namespace Geometry
{
	Triangle::Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c) : Shape(Type::TRIANGLE)
	{
		init(a, b, c);
	}

	Triangle::Triangle(Utils::Vec3 & a, Utils::Vec3 & b, Utils::Vec3 & c, const Utils::Mat4 & transformation) : Shape(Type::TRIANGLE, transformation)
	{
		init(a, b, c);
	}

	Triangle::Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c, const Utils::Mat4 &transformation, const Processing::MaterialProps &material) : Shape(Type::TRIANGLE, transformation, material)
	{
		init(a, b, c);
	}

	void Triangle::init(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c)
	{
		using Utils::Operations;
		if (a == b || a == c || b == c)
		{
			throw new std::exception("A triangle is made up of three distinct vertices");
		}

		this->a = Operations::vectorTransform(transformation, a);
		this->b = Operations::vectorTransform(transformation, b);
		this->c = Operations::vectorTransform(transformation, c);
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
		return Operations::normalize(normal);
	}


	Shape::BarryCentricCoordinates Triangle::getBarryCentricCoordinates(const Processing::Ray &ray, float &determinant, float &t)
	{
		return _BCC(ray, determinant, t);
	}

	Shape::BarryCentricCoordinates Triangle::getBarryCentricCoordinates(const Processing::Ray &ray)
	{
		float dummy = 0.0f;
		return _BCC(ray, dummy, dummy);
	}

	Shape::BarryCentricCoordinates Triangle::_BCC(const Processing::Ray &ray, float &determinant, float &t)
	{
		using Utils::Vec3, Utils::Operations;
		Vec3 direction = ray.getDirection();
		Vec3 edge0 = getEdge0();
		Vec3 edge1 = getEdge1();
		Vec3 P = Operations::cross(direction, edge1);
		determinant = Operations::dot(edge0, P);
		float invertedDeterminant = 1 / determinant;

		Vec3 triangleToOrigin = ray.getOrigin() - getA();
		float u = invertedDeterminant * Operations::dot(triangleToOrigin, P);

		Vec3 q = Operations::cross(triangleToOrigin, edge0);
		float v = invertedDeterminant * Operations::dot(direction, q);
		// Possible intersection
		t = invertedDeterminant * Operations::dot(edge1, q);

		BarryCentricCoordinates coordinates;
		coordinates.push_back(u);
		coordinates.push_back(v);
		return coordinates;
	}

	std::optional<float> Triangle::intersect(const Processing::Ray &ray)
	{
		float determinant = 0.0f, t = 0.0f;
		BarryCentricCoordinates coordinates = getBarryCentricCoordinates(ray, determinant, t);
		// A determinant that is close to 0 indicates that it does not intersect.
		// Also catches back-facing triangles, as those will have a negative determinant.
		if (determinant < std::numeric_limits<float>::epsilon()) {
			return std::nullopt;
		}

		float u = coordinates.at(0);
		float v = coordinates.at(1);
		if (u < 0 || u > 1) {
			return std::nullopt;
		}

		if (v < 0 || u + v > 1) {
			return std::nullopt;
		}

		if (t < std::numeric_limits<float>::epsilon()) {
			return std::nullopt;
		}

		return t;
	}

	Utils::Vec3 Triangle::normalAtPoint(const Processing::Ray &ray, float t)
	{
		return getNormal();
	}
}