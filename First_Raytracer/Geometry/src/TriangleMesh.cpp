#include "../TriangleMesh.h"
#include "../Triangle.h"
#include "../Utils/Operations.h"

namespace Geometry
{
	const Utils::Vec3& TriangleMesh::getVertex(int index) const
	{
		return vertices.at(index);
	}

	void TriangleMesh::pushNormal(const Utils::Vec3 &normal)
	{
		checkState();
		normals.push_back(normal);
		manualNormals = true;
	}

	void TriangleMesh::pushVertex(const Utils::Vec3 &vertex)
	{
		checkState();
		vertices.push_back(vertex);
		boundingBox.extendBoundary(vertex);
		vertexCount++;
	}

	void TriangleMesh::applyTransformation()
	{
		checkState();
		for (Utils::Vec3 &vertex : vertices) {
			Utils::Vec3 transformedVertex = Utils::Operations::vectorTransform(transformation, vertex, true);
			vertex = transformedVertex;
			boundingBox.extendBoundary(transformedVertex);
		}

		ensureNormals();
		for (Utils::Vec3 &normal : normals) {
			normal = Utils::Operations::normalize(Utils::Operations::vectorTransform(normalTransformation, normal, false));
		}
	}

	bool TriangleMesh::isFinalized()
	{
		return meshFinalized;
	}

	void TriangleMesh::ensureNormals()
	{
		checkState();
		if (manualNormals) {
			return;
		}

		for (const Utils::Vec3 &vertex : vertices) {
			normals.push_back(Utils::Vec3(0.0f, 0.0f, 0.0f));
		}

		for (const TriIndex &face : faces) {
			Utils::Vec3 normalContribution = Triangle(vertices[face.v0], vertices[face.v1], vertices[face.v2]).getNormal();
			normals.at(face.v0) += normalContribution;
			normals.at(face.v1) += normalContribution;
			normals.at(face.v2) += normalContribution;
		}
	}

	void TriangleMesh::checkState()
	{
		if (isFinalized())
		{
			throw new std::exception("Triangle mesh has been finalized, and cannot be changed");
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
		checkState();
		this->faces = faces;
	}

	const TriangleMesh::TriIndex& TriangleMesh::getTriangle(int index) const
	{
		return faces.at(index);
	}

	void TriangleMesh::commitTriangle(int v0, int v1, int v2)
	{
		checkState();
		faces.push_back(TriIndex{ v0, v1, v2 });
	}

	void TriangleMesh::finalize()
	{
		if (meshFinalized) {
			return;
		}

		applyTransformation();
		meshFinalized = true;
	}

	std::optional<float> TriangleMesh::intersect(const Processing::Ray &ray)
	{
		if (!meshFinalized) {
			finalize();
		}

		bool intersectedBox = boundingBox.intersect(ray);
		if (!intersectedBox) {
			return std::nullopt;
		}

		float nearT = std::numeric_limits<float>::infinity();
		for (const TriIndex &face : faces) {
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

	Utils::Vec3 TriangleMesh::normalAtPoint(const Processing::Ray &ray, float t)
	{
		if (intersectedFace == nullptr) {
			throw new std::exception("Error: Cannot get normal of intersected triangle if no triangle has been intersected within mesh");
		}
		// Using Gouraud shading
		Triangle triangle(vertices[intersectedFace->v0], vertices[intersectedFace->v1], vertices[intersectedFace->v2]);
		BarryCentricCoordinates coordinates = triangle.getBarryCentricCoordinates(ray);
		float u = coordinates[0];
		float v = coordinates[1];
		float w = 1.0f - u - v;

		return Utils::Operations::normalize(w * normals[intersectedFace->v0] + u * normals[intersectedFace->v1] + v * normals[intersectedFace->v2]);
	}
}