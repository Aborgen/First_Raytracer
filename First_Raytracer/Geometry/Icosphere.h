#ifndef ICOSPHERE_H
#define ICOSPHERE_H
#pragma once

#include <unordered_map>

#include "TriangleMesh.h"
#include "../Utils/Mat4.h"
#include "../Utils/Vec3.h"
#include "../MaterialProps/MaterialProps.h"

namespace Geometry
{
	// Class is based on this one by Andreas Kahler
	// http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	class Icosphere : public TriangleMesh
	{
	public:
		enum class Detail
		{
			ICOSAHEDRON,
			ROUGH,
			MODERATE,
			BEST
		};

		Icosphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f), detail(Detail::BEST) {};
		Icosphere(const Utils::Vec3 &center, float radius, const Utils::Mat4 &transformation,
				  const Processing::MaterialProps &material, Detail detail = Detail::BEST) :
			TriangleMesh(transformation, material), center(center), radius(radius), detail(detail) { init(); };

	private:
		typedef std::unordered_map<int64_t, int> middlePointIndexCache;
		Utils::Vec3 center;
		float radius;
		const Detail detail;
		void init();
		void refine();
		int getMiddlePoint(int p0, int p1, middlePointIndexCache &idxCache);
		int recursionDepth();
	};
}

#endif // !ICOSPHERE_H
