#include "../Sphere.h"
#include "../../Utils/Operations.h"

namespace Geometry
{
	Sphere::Sphere(const Utils::Vec3 &center, float radius, const Utils::Mat4 &transformation, const Processing::MaterialProps &material) : Shape(Type::SPHERE, transformation, material)
	{
		this->center = center;
		this->radius = radius;
		transformSphere();
	}

	void Sphere::transformSphere()
	{
		center += Utils::Vec3(transformation[0][3], transformation[1][3], transformation[2][3]);
		radius *= transformation[0][0];
	}

	std::optional<float> Sphere::intersect(const Processing::Ray &ray)
	{
		using namespace Utils;
		Vec3 origin = ray.getOrigin();
		Vec3 direction = ray.getDirection();
		Vec3 delta = origin - center;
		// Set up quadratic equation
		float a = Operations::dot(direction, direction);
		float b = 2 * Operations::dot(direction, delta);
		float c = Operations::dot(delta, delta) - std::pow(radius, 2);
		std::optional<float> intersection = findClosestRoot(a, b, c);
		if (!intersection.has_value()) {
			return std::nullopt;
		}

		return intersection.value();
	}

	std::optional<float> Sphere::findClosestRoot(float a, float b, float c)
	{
		float discriminant = std::pow(b, 2) - 4 * a * c;
		// There are no real roots
		if (discriminant < 0) {
			return std::nullopt;
		}

		float root;
		// There is one real root
		if (discriminant == 0) {
			root = (-b / a) / 2.0f;
		}
		else {
			float sign = b > 0 ? 1.0f : -1.0f;
			float quadratic = -0.5f * b + sign * sqrt(discriminant);
			float root1 = quadratic / a;
			float root2 = c / quadratic;
			if (root1 > 0 && root1 < root2) {
				root = root1;
			}
			else if (root2 > 0) {
				root = root2;
			}
			else {
				return std::nullopt;
			}
		}

		return root;
	}

	Utils::Vec3 Sphere::normalAtPoint(const Utils::Vec3 &point)
	{
		Utils::Vec3 normal = point - center;
		normal = Utils::Operations::normalize(normal);
		return normal;
	}
}