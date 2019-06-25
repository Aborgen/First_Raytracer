#ifndef SPHERE_H
#define SPHERE_H
#pragma once

#include <optional>

#include "Shape.h"

namespace Geometry
{
	class Sphere : public Shape
	{
	public:
		Sphere() : Shape(Type::SPHERE) {}
		Sphere(const Utils::Vec3 &center, float radius, const Utils::Mat4 &transformation, const Processing::MaterialProps &material);
		std::optional<float> intersect(const Processing::Ray &ray);

	private:
		Utils::Vec3 center;
		float radius;
		void transformSphere();
		std::optional<float> findClosestRoot(float a, float b, float c);
		Utils::Vec3 normalAtPoint(const Utils::Vec3 &point);
	};
}

#endif // !SPHERE_H
