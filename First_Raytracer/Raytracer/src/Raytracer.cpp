#include <optional>

#include "../Raytracer.h"
#include "../Utils/Operations.h"

namespace Processing
{
	Utils::ColorTriad Raytracer::trace(const Ray &ray)
	{
		IntersectionInfo info;
		return traceRecursive(ray, info);
	}

	Utils::ColorTriad Raytracer::traceRecursive(const Ray &ray, IntersectionInfo info, int currentDepth)
	{
		if (currentDepth > maxDepth) {
			return Utils::ColorTriad(0.0f, 0.0f, 0.0f);
		}

		bool intersection = traceClosest(ray, info);
		if (!intersection) {
			if (ray.getType() == Ray::Type::RECURSIVE) {
				return Utils::ColorTriad(0.0f, 0.0f, 0.0f);
			}

			return backgroundColor;
		}

		Utils::Vec3 normal = info.shape->normalAtPoint(ray, info.t);
		Utils::Vec3 point = ray.specificPoint(info.t);
		if (info.shape->getType() == Geometry::Shape::Type::TRIANGLE_MESH) {
			point += normal * 2e-4f;
		}

		MaterialProps material = info.shape->getMaterial();
		Utils::ColorTriad finalColor = material.getAmbient() + material.getEmission();
		for (const LightPtr &light : lights) {
			Utils::Vec3 direction;
			IntersectionInfo shadowInfo;
			if (light->getType() == Light::Type::DIRECTIONAL) {
				// Many resources seem to indicate that lighting engines expect the directional vector
				// from directional light sources to be negated (-<i, j, k> = <-i, -j, -k>). This is due
				// to the light's stored vector often being a direction which points away from the light source.
				// In the case of this course, however, doing so would be physically incorrect, as the assignment
				// specifies that the numbers given already represent a direction going towards the light source.
				direction = light->getCoordinates();
			}
			else if (light->getType() == Light::Type::POINT) {
				direction = light->getCoordinates() - point;
				// This is to ensure that there can be no intersections occuring beyond the point light's position.
				shadowInfo.t = direction.length();
			}

			// Setting the IntersectionInfo's shape member ensures that the shadow ray cannot intersect that specific shape.
			shadowInfo.shape = info.shape;
			Ray shadowRay(point, direction, Ray::Type::SHADOW);
			bool lightOccluded = traceClosest(shadowRay, shadowInfo);
			// In this case, the ray intersects a shape before reaching the light.
			if (lightOccluded) {
				continue;
			}

			Utils::Vec3 half = Utils::Operations::normalize(shadowRay.getDirection() + ray.getDirection().reverse());
			finalColor += computeLight(shadowRay.getDirection(), normal, half, light, material);
		}


		Utils::ColorTriad reflection, specular = material.getSpecular();
		if (specular.getR() + specular.getG() + specular.getB() > 0.0f) {
			reflection = specular * computeReflection(ray.getDirection(), point, normal, info.shape, currentDepth);
		}

		return finalColor + reflection;
	}

	bool Raytracer::traceClosest(const Ray &ray, IntersectionInfo &info)
	{
		bool anyIntersection = false;
		ShapePtr originatingShape = info.shape;
		for (const ShapePtr &shape : shapes) {
			// When we are tracing a shadow/recursive ray, we have set info.shape to be the shape that has
			// been intersected by the primary ray. If that hasn't happened, the default is nullptr.
			if (ray.getType() != Ray::Type::PRIMARY && originatingShape != nullptr) {
				// It is impossible for a shape's shadow ray to intersect the originating shape unless it is a mesh.
				// Skip it.
				if (originatingShape->getType() != Geometry::Shape::Type::TRIANGLE_MESH && shape == originatingShape) {
					continue;
				}
			}

			std::optional<float> optIntersection = shape->intersect(ray);
			// No intersection between ray and shape.
			if (!optIntersection.has_value()) {
				continue;
			}

			float intersection = optIntersection.value();
			if (intersection < info.t) {
				info.t = intersection;
				info.shape = shape;
				anyIntersection = true;
			}
		}

		return anyIntersection;
	}

	Utils::ColorTriad Raytracer::computeLight(const Utils::Vec3 &direction, const Utils::Vec3 &normal, const Utils::Vec3 &half, const LightPtr &light, const MaterialProps &material)
	{
		using Utils::ColorTriad, Utils::Operations;
		ColorTriad lambert, diffuse = material.getDiffuse();
		if (diffuse.getR() + diffuse.getG() + diffuse.getB() > 0.0f) {
			lambert = diffuse * std::max(Operations::dot(normal, direction), 0.0f);
		}

		ColorTriad phong, specular = material.getSpecular();
		if (specular.getR() + specular.getG() + specular.getB() > 0.0f) {
			phong = specular * std::pow(std::max(Operations::dot(normal, half), 0.0f), material.getShininess());
		}

		ColorTriad attenuation = light->getColor();
		if (light->getType() == Light::Type::POINT) {
			float distance = direction.length();
			attenuation = light->getAttenuation().compute(light->getColor(), distance);
		}

		return attenuation * (lambert + phong);
	}

	Utils::ColorTriad Raytracer::computeReflection(const Utils::Vec3 &incidentDirection, const Utils::Vec3 &hitPoint, const Utils::Vec3 &normal, const ShapePtr &shape, int currentDepth)
	{
		using Utils::ColorTriad, Utils::Vec3, Utils::Operations;
		Vec3 reflectedDirection = incidentDirection - 2 * Operations::dot(normal, incidentDirection) * normal;
		IntersectionInfo info;
		// Setting the IntersectionInfo's shape member ensures that the recursive ray cannot intersect that specific shape.
		info.shape = shape;
		return traceRecursive(Ray(hitPoint, reflectedDirection, Ray::Type::RECURSIVE), info, currentDepth + 1);
	}
}