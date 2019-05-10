#ifndef RAYTRACER_H
#define RAYTRACER_H
#pragma once

#include "../Types/LightPtr.h"
#include "../Types/ShapePtr.h"
#include "../Utils/ColorTriad.h"

namespace Processing
{
	class Raytracer
	{
	public:
		Raytracer() {};
		Raytracer(const LightDeque &lights, const ShapeDeque &shapes);
		Utils::ColorTriad trace(const Ray &ray) const;

	private:
		LightDeque lights;
		ShapeDeque shapes;
	};
}

#endif // !RAYTRACER_H
