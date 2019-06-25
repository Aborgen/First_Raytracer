#include <unordered_set>

#include "../Icosphere.h"
#include "../../Utils/Operations.h"

namespace Geometry
{
	void Icosphere::init()
	{
		using Utils::Operations;
		using Utils::Vec3;
		float phi = (1.0f + std::sqrt(5.0f)) / 2.0f;
		// First, the vertices of three orthagonal rectangles are constructed.
		// Rectangle orientated along y-axis
		pushVertex(Operations::normalize(Vec3(-1.0f,  phi, 0.0f)));
		pushVertex(Operations::normalize(Vec3( 1.0f,  phi, 0.0f)));
		pushVertex(Operations::normalize(Vec3(-1.0f, -phi, 0.0f)));
		pushVertex(Operations::normalize(Vec3( 1.0f, -phi, 0.0f)));
		// Rectangle orientated along z-axis
		pushVertex(Operations::normalize(Vec3(0.0f, -1.0f,  phi)));
		pushVertex(Operations::normalize(Vec3(0.0f,  1.0f,  phi)));
		pushVertex(Operations::normalize(Vec3(0.0f, -1.0f, -phi)));
		pushVertex(Operations::normalize(Vec3(0.0f,  1.0f, -phi)));
		// Rectangle orientated along x-axis
		pushVertex(Operations::normalize(Vec3( phi, 0.0f, -1.0f)));
		pushVertex(Operations::normalize(Vec3( phi, 0.0f,  1.0f)));
		pushVertex(Operations::normalize(Vec3(-phi, 0.0f, -1.0f)));
		pushVertex(Operations::normalize(Vec3(-phi, 0.0f,  1.0f)));

		// Next, the vertices of the rectangles are joined together to form a series of triangle faces.
		// 5 faces around point 0
		commitTriangle(0, 11, 5);
		commitTriangle(0, 5, 1);
		commitTriangle(0, 1, 7);
		commitTriangle(0, 7, 10);
		commitTriangle(0, 10, 11);
		// 5 adjacent faces
		commitTriangle(1, 5, 9);
		commitTriangle(5, 11, 4);
		commitTriangle(11, 10, 2);
		commitTriangle(10, 7, 6);
		commitTriangle(7, 1, 8);
		// 5 faces around point 3
		commitTriangle(3, 9, 4);
		commitTriangle(3, 4, 2);
		commitTriangle(3, 2, 6);
		commitTriangle(3, 6, 8);
		commitTriangle(3, 8, 9);
		// 5 adjacent faces
		commitTriangle(4, 9, 5);
		commitTriangle(2, 4, 11);
		commitTriangle(6, 2, 10);
		commitTriangle(8, 6, 7);
		commitTriangle(9, 8, 1);
		// The triangle faces are then broken up into smaller and smaller triangles, 
		// dependant on what level of detail is desired.

		for (int _ = 0; _ < recursionDepth(); _++) {
			refine();
		}

		applyTransformation();
	}

	// Each triangle is broken down into four new triangles.
	// There are three outer triangles, as well as a fourth that makes up the center.
	// Think Triforce.
	void Icosphere::refine()
	{
		middlePointIndexCache idxCache;
		std::vector<TriIndex> nextFaces;
		const std::vector<TriIndex> &faces = getFaces();
		for (const TriIndex &face : faces) {
			int a = getMiddlePoint(face.v0, face.v1, idxCache);
			int b = getMiddlePoint(face.v1, face.v2, idxCache);
			int c = getMiddlePoint(face.v2, face.v0, idxCache);

			nextFaces.push_back(TriIndex{ face.v0, a, c });
			nextFaces.push_back(TriIndex{ face.v1, b, a });
			nextFaces.push_back(TriIndex{ face.v2, c, b });
			nextFaces.push_back(TriIndex{ a, b, c });
		}

		idxCache.clear();
		setFaces(nextFaces);
	}

	int Icosphere::getMiddlePoint(int p0, int p1, middlePointIndexCache &idxCache)
	{
		using Utils::Operations;
		using Utils::Vec3;
		if (p0 > p1) {
			std::swap(p0, p1);
		}

		int64_t key = ((int64_t)p0 << 32) + p1;
		auto iter = idxCache.find(key);
		if (iter != idxCache.end()) {
			return iter->second;
		}

		Vec3 point0 = getVertex(p0);
		Vec3 point1 = getVertex(p1);
		Vec3 middle = 0.5f * (point0 + point1);
		pushVertex(Operations::normalize(middle));

		int index = getVertexIndex();
		idxCache[key] = index;
		return index;
	}

	int Icosphere::recursionDepth()
	{
		switch (detail) {
		case Detail::ROUGH:
			return 1;
		case Detail::MODERATE:
			return 2;
		case Detail::BEST:
			return 3;
		case Detail::ICOSAHEDRON:
		// Fall through
		default:
			return 0;
		}
	}
}