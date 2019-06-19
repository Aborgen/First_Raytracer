#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#pragma once

#include "AccelerationStructure.h"
#include "../Utils/Vec3.h"

namespace Processing
{
	class BoundingBox : public AccelerationStructure
	{
	public:
		BoundingBox() {};
		void extendBoundary(const Utils::Vec3 &vertex);
		bool intersect(const Ray &ray);

	private:
		Utils::Vec3 minimumBound{ 0.0f, 0.0f, 0.0f };
		Utils::Vec3 maximumBound{ 0.0f, 0.0f, 0.0f };
	};
}
#endif // !BOUNDINGBOX_H
