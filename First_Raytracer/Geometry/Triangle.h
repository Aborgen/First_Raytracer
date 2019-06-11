#ifndef TRIANGLE_H
#define TRIANGLE_H
#pragma once

#include "Shape.h"
#include "../Utils/Vec3.h"

namespace Geometry
{
	class Triangle : public Shape
	{
	public:
		Triangle() : Shape(Type::TRIANGLE) {};
		Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c, const Utils::Mat4 &transformation, const Processing::MaterialProps &material);
		Utils::Vec3 getA();
		Utils::Vec3 getB();
		Utils::Vec3 getC();

		Utils::Vec3 getEdge0();
		Utils::Vec3 getEdge1();
		Utils::Vec3 getEdge2();
		Utils::Vec3 getNormal();
		std::optional<float> intersect(const Processing::Ray &ray);
		Utils::Vec3 normalAtPoint(const Utils::Vec3 &point);

	private:
		Utils::Vec3 a;
		Utils::Vec3 b;
		Utils::Vec3 c;
	};
}

#endif // !TRIANGLE_H
