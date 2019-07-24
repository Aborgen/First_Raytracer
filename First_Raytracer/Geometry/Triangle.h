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
		Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c);
		Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c, const Utils::Mat4 &transformation);
		Triangle(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c, const Utils::Mat4 &transformation, const Processing::MaterialProps &material);
		void init(Utils::Vec3 &a, Utils::Vec3 &b, Utils::Vec3 &c);
		Utils::Vec3 getA();
		Utils::Vec3 getB();
		Utils::Vec3 getC();

		Utils::Vec3 getEdge0();
		Utils::Vec3 getEdge1();
		Utils::Vec3 getEdge2();
		Utils::Vec3 getNormal();
		BarryCentricCoordinates getBarryCentricCoordinates(const Processing::Ray &ray, float &determinant, float &t);
		BarryCentricCoordinates getBarryCentricCoordinates(const Processing::Ray &ray);
		std::optional<float> intersect(const Processing::Ray &ray);
		Utils::Vec3 normalAtPoint(const Processing::Ray &ray, float t);

	private:
		Utils::Vec3 a;
		Utils::Vec3 b;
		Utils::Vec3 c;
		BarryCentricCoordinates _BCC(const Processing::Ray &ray, float &determinant, float &t);
	};
}

#endif // !TRIANGLE_H
