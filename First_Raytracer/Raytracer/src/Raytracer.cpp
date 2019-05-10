#include <optional>

#include "../Raytracer.h"
#include "../../MaterialProps/MaterialProps.h"

namespace Processing
{
	Raytracer::Raytracer(const LightDeque &lights, const ShapeDeque &shapes)
	{
		this->lights = lights;
		this->shapes = shapes;
	}

	Utils::ColorTriad Raytracer::trace(const Ray &ray) const
	{
		Utils::ColorTriad color = Utils::ColorTriad();
		float closestIntersection = std::numeric_limits<float>::infinity();
		for (const ShapePtr &shape : shapes) {
			std::optional<float> optIntersection = shape->intersect(ray);
			// No intersection between ray and shape.
			if (!optIntersection.has_value()) {
				continue;
			}

			float intersection = optIntersection.value();
			if (intersection < closestIntersection) {
				closestIntersection = intersection;
				color.setR(1.0f);
				break;
			}

			//MaterialProps material = shape->getMaterial();
			//break;
		}

		return color;
	}
}