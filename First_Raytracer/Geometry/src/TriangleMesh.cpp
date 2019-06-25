#include "../TriangleMesh.h"
#include "../Triangle.h"
#include "../Utils/Operations.h"

namespace Geometry
{
	const Utils::Vec3& TriangleMesh::getVertex(int index) const
	{
		return vertices.at(index);
	}

	//void TriangleMesh::pushVertex(const Utils::Vec3 &vertex)
	//{
	//	Utils::Vec3 transformedVertex = Utils::Operations::vectorTransform(transformation, vertex);
	//	vertices.push_back(transformedVertex);
	//	boundingBox.extendBoundary(transformedVertex);
	//	vertexCount++;
	//}

	void TriangleMesh::pushVertex(const Utils::Vec3 &vertex)
	{
		vertices.push_back(vertex);
		boundingBox.extendBoundary(vertex);
		vertexCount++;
	}

	void TriangleMesh::applyTransformation()
	{
		for (Utils::Vec3 &vertex : vertices) {
			Utils::Vec3 transformedVertex = Utils::Operations::vectorTransform(transformation, vertex);
			vertex = transformedVertex;
			boundingBox.extendBoundary(transformedVertex);
		}
	}

	const int TriangleMesh::getVertexIndex() const
	{
		return vertexCount > 0 ? vertexCount - 1 : 0;
	}

	const std::vector<TriangleMesh::TriIndex>& TriangleMesh::getFaces() const
	{
		return faces;
	}

	void TriangleMesh::setFaces(const std::vector<TriIndex> &faces)
	{
		this->faces = faces;
	}

	const TriangleMesh::TriIndex& TriangleMesh::getTriangle(int index) const
	{
		return faces.at(index);
	}

	void TriangleMesh::commitTriangle(int v0, int v1, int v2)
	{
		faces.push_back(TriIndex{ v0, v1, v2 });
	}

	std::optional<float> TriangleMesh::intersect(const Processing::Ray &ray)
	{
		bool intersectedBox = boundingBox.intersect(ray);
		if (!intersectedBox) {
			return std::nullopt;
		}

		float nearT = std::numeric_limits<float>::infinity();
		int identicalTriangles = 0;
		for (const TriIndex &face : faces) {
			auto o = vertices[face.v0];
			auto u = vertices[face.v1];
			auto j = vertices[face.v2];

			if (o == u || o == j || o == u) {
				identicalTriangles++;
			}
			Triangle triangle(vertices[face.v0], vertices[face.v1], vertices[face.v2]);
			std::optional<float> optIntersection = triangle.intersect(ray);
			// No intersection between ray and triangle.
			if (!optIntersection.has_value()) {
				continue;
			}

			float intersection = optIntersection.value();
			if (intersection < nearT) {
				nearT = intersection;
				intersectedFace = std::make_shared<TriIndex>(face);
			}
		}

		if (intersectedFace == nullptr) {
			return std::nullopt;
		}

		return nearT;
	}

	Utils::Vec3 TriangleMesh::normalAtPoint(const Utils::Vec3 &point)
	{
		if (intersectedFace == nullptr) {
			throw new std::exception("Error: Cannot get normal of intersected triangle if no triangle has been intersected within mesh");
		}

		Triangle triangle(vertices[intersectedFace->v0], vertices[intersectedFace->v1], vertices[intersectedFace->v2]);
		//return Utils::Operations::vectorTransform(normalTransformation, triangle.getNormal());
		return triangle.getNormal();
	}
}