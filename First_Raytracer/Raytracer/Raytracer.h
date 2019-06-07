#ifndef RAYTRACER_H
#define RAYTRACER_H
#pragma once

#include "../MaterialProps/MaterialProps.h"
#include "../Types/LightPtr.h"
#include "../Types/ShapePtr.h"
#include "../Utils/ColorTriad.h"
#include "../Utils/Vec4.h"

namespace Processing
{
	struct IntersectionInfo
	{
		ShapePtr shape = nullptr;
		float t = std::numeric_limits<float>::infinity();
	};

	class Raytracer
	{
	public:
		Raytracer() {};
		Raytracer(const LightDeque &lights, const ShapeDeque &shapes) : lights(lights), shapes(shapes), backgroundColor(0.0f, 0.0f, 0.0f) {};
		Raytracer(const LightDeque &lights, const ShapeDeque &shapes, const Utils::ColorTriad &backgroundColor) : lights(lights), shapes(shapes), backgroundColor(backgroundColor) {};
		Utils::ColorTriad trace(const Ray &ray);


	private:
		LightDeque lights;
		ShapeDeque shapes;
		Utils::ColorTriad backgroundColor;
		bool traceClosest(const Ray &ray, IntersectionInfo &info);
		Utils::ColorTriad computeLight(const Utils::Vec3 &direction, const Utils::Vec3 &normal, const Utils::Vec3 &half, const LightPtr &light, const MaterialProps &material);
	};
}

#endif // !RAYTRACER_H
