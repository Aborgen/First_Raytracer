#include <optional>

#include "../Raytracer.h"
#include "../Utils/Operations.h"

namespace Processing
{
	Utils::ColorTriad Raytracer::trace(const Ray &ray)
	{
		IntersectionInfo info;
		bool intersection = traceClosest(ray, info);
		if (!intersection) {
			return backgroundColor;
		}

		Utils::Vec3 point = ray.specificPoint(info.t);
		Utils::Vec3 normal = info.shape->normalAtPoint(point);
		MaterialProps material = info.shape->getMaterial();
		Utils::ColorTriad finalColor = material.getAmbient() + material.getEmission();
		for (const LightPtr &light : lights) {
			Utils::Vec3 direction;
			Light::Type type = light->getType();
			if (type == Light::Type::DIRECTIONAL) {
				direction = light->getCoordinates().reverse();
			}
			else if (type == Light::Type::POINT) {
				direction = light->getCoordinates() - point;
			}

			Ray shadowRay(point + normal, direction, Ray::Type::SHADOW);
			IntersectionInfo _unused;
			bool lightOcculded = traceClosest(shadowRay, _unused);
			// In this case, the ray intersects a shape before reaching the light.
			if (lightOcculded) {
				continue;
			}

			Utils::Vec3 half = ray.getDirection() + shadowRay.getDirection();
			half = Utils::Operations::normalize(half);
			finalColor += computeLight(shadowRay.getDirection(), normal, half, light, material);
		}

		return finalColor;
	}

	bool Raytracer::traceClosest(const Ray &ray, IntersectionInfo &info)
	{
		for (const ShapePtr &shape : shapes) {
			std::optional<float> optIntersection = shape->intersect(ray);
			// No intersection between ray and shape.
			if (!optIntersection.has_value()) {
				continue;
			}

			float intersection = optIntersection.value();
			if (intersection < info.t) {
				// A shadow ray is only concerned if ANY shape is intersected
				if (ray.getType() == Ray::Type::SHADOW) {
					return true;
				}

				info.t = intersection;
				info.shape = shape;
			}
		}

		return info.shape != nullptr;
	}

	Utils::ColorTriad Raytracer::computeLight(const Utils::Vec3 &direction, const Utils::Vec3 &normal, const Utils::Vec3 &half, const LightPtr &light, const MaterialProps &material)
	{
		using namespace Utils;
		float normalDotDirection = Operations::dot(normal, direction);
		float normalDotHalf = Operations::dot(normal, half);
		ColorTriad lightColor = light->getColor();
		ColorTriad lambert = material.getDiffuse() * lightColor * std::max(normalDotDirection, 0.0f);
		ColorTriad phong = material.getSpecular() *	lightColor * std::pow(std::max(normalDotHalf, 0.0f), material.getShininess());
		return lambert + phong;
	}
}