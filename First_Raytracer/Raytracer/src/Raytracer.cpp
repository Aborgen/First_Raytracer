#include <optional>

#include "../Raytracer.h"
#include "../Utils/Operations.h"

namespace Processing
{
	Utils::ColorTriad Raytracer::trace(const Ray &ray)
	{
		return traceRecursive(ray);
	}

	Utils::ColorTriad Raytracer::traceRecursive(const Ray &ray, int currentDepth)
	{
		if (currentDepth >= maxDepth) {
			return Utils::ColorTriad(0.0f, 0.0f, 0.0f);
		}

		IntersectionInfo info;
		bool intersection = traceClosest(ray, info);
		if (!intersection) {
			if (ray.getType() == Ray::Type::RECURSIVE) {
				return Utils::ColorTriad(0.0f, 0.0f, 0.0f);
			}

			return backgroundColor;
		}

		Utils::Vec3 point = ray.specificPoint(info.t);
		Utils::Vec3 normal = info.shape->normalAtPoint(point);
		MaterialProps material = info.shape->getMaterial();
		Utils::ColorTriad finalColor = material.getAmbient() + material.getEmission();
		for (const LightPtr &light : lights) {
			Utils::Vec3 direction;
			IntersectionInfo shadowInfo;
			Light::Type type = light->getType();
			if (type == Light::Type::DIRECTIONAL) {
				direction = light->getCoordinates().reverse();
			}
			else if (type == Light::Type::POINT) {
				direction = light->getCoordinates() - point;
				shadowInfo.t = sqrt(direction.length());
			}

			Utils::Vec3 biasedOrigin = point + normal * 2e-4f;
			Ray shadowRay(biasedOrigin, direction, Ray::Type::SHADOW);
			bool lightOccluded = traceClosest(shadowRay, shadowInfo);
			// In this case, the ray intersects a shape before reaching the light.
			if (lightOccluded && shadowInfo.shape != info.shape) {
				continue;
			}

			Utils::ColorTriad reflection, specular = material.getSpecular();
			if (specular.getR() + specular.getG() + specular.getB() > 0.0f) {
				reflection = specular * computeReflection(ray.getDirection(), biasedOrigin, normal, currentDepth);
			}

			Utils::Vec3 half = Utils::Operations::normalize(shadowRay.getDirection() + ray.getDirection().reverse());
			finalColor += computeLight(shadowRay.getDirection(), normal, half, light, material) + reflection;
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
				info.t = intersection;
				info.shape = shape;
			}
		}

		return info.shape != nullptr;
	}

	Utils::ColorTriad Raytracer::computeLight(const Utils::Vec3 &direction, const Utils::Vec3 &normal, const Utils::Vec3 &half, const LightPtr &light, const MaterialProps &material)
	{
		using Utils::ColorTriad, Utils::Operations;
		ColorTriad lambert, diffuse = material.getDiffuse();
		if (diffuse.getR() + diffuse.getG() + diffuse.getB() > 0.0f) {
			lambert = diffuse * light->getColor() * std::max(Operations::dot(normal, direction), 0.0f);
		}

		ColorTriad phong, specular = material.getSpecular();
		if (specular.getR() + specular.getG() + specular.getB() > 0.0f) {
			phong = specular * light->getColor() * std::pow(std::max(Operations::dot(normal, half), 0.0f), material.getShininess());
		}
		
		return lambert + phong;
	}

	Utils::ColorTriad Raytracer::computeReflection(const Utils::Vec3 &incidentDirection, const Utils::Vec3 &hitPoint, const Utils::Vec3 &normal, int currentDepth)
	{
		using Utils::ColorTriad, Utils::Vec3, Utils::Operations;
		Vec3 reflectedDirection = incidentDirection - 2 * Operations::dot(normal, incidentDirection) * normal;
		return traceRecursive(Ray(hitPoint, reflectedDirection, Ray::Type::RECURSIVE), currentDepth + 1);
	}
}