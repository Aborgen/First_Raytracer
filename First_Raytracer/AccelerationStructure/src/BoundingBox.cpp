#include <algorithm>
#include <limits>

#include "../BoundingBox.h"

namespace Processing
{
	void BoundingBox::extendBoundary(const Utils::Vec3 &vertex)
	{
		using std::min, std::max, Utils::Vec3;
		minimumBound = Vec3(min(minimumBound.getX(), vertex.getX()), min(minimumBound.getY(), vertex.getY()), min(minimumBound.getZ(), vertex.getZ()));
		maximumBound = Vec3(max(maximumBound.getX(), vertex.getX()), max(maximumBound.getY(), vertex.getY()), max(maximumBound.getZ(), vertex.getZ()));
	}

	// Intersection formula taken from Tavian Barnes
	// https://tavianator.com/fast-branchless-raybounding-box-intersections/
	bool BoundingBox::intersect(const Ray &ray)
	{
		Utils::Vec3 origin = ray.getOrigin();
		Utils::Vec3 direction = ray.getDirection();
		Utils::Vec3 inversedDirection(1 / direction.getX(), 1 / direction.getY(), 1 / direction.getZ());
		float tx1 = (minimumBound.getX() - origin.getX()) * inversedDirection.getX();
		float tx2 = (maximumBound.getX() - origin.getX()) * inversedDirection.getX();
		float tmin = std::min(tx1, tx2);
		float tmax = std::max(tx1, tx2);

		float ty1 = (minimumBound.getY() - origin.getY()) * inversedDirection.getY();
		float ty2 = (maximumBound.getY() - origin.getY()) * inversedDirection.getY();
		tmin = std::max(tmin, std::min(ty1, ty2));
		tmax = std::min(tmax, std::max(ty1, ty2));

		float tz1 = (minimumBound.getZ() - origin.getZ()) * inversedDirection.getZ();
		float tz2 = (maximumBound.getZ() - origin.getZ()) * inversedDirection.getZ();
		tmin = std::max(tmin, std::min(tz1, tz2));
		tmax = std::min(tmax, std::max(tz1, tz2));
		return tmax >= tmin;
	}
}