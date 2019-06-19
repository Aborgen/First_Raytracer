#ifndef ACCELERATIONSTRUCTURE_H
#define ACCELERATIONSTRUCTURE_H
#pragma once

#include "../Ray/Ray.h"

namespace Processing
{
	class AccelerationStructure
	{
	public:
		virtual bool intersect(const Ray &ray) = 0;
		virtual ~AccelerationStructure() {};

	protected:
		AccelerationStructure() {};
	};
}

#endif // !ACCELERATIONSTRUCTURE_H
