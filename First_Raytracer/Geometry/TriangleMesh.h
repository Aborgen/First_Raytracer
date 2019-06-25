#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#pragma once

#include <exception>
#include <memory>
#include <vector>

#include "Shape.h"
#include "../AccelerationStructure/BoundingBox.h"
#include "../Utils/Vec3.h"

namespace Geometry
{
	class TriangleMesh : public Shape
	{
	protected:
		struct TriIndex
		{
			int v0;
			int v1;
			int v2;
		};

		const Utils::Vec3& getVertex(int index) const;
		const TriIndex& getTriangle(int index) const;
		const int getVertexIndex() const;
		const std::vector<TriIndex>& getFaces() const;
		void setFaces(const std::vector<TriIndex> &faces);
		void applyTransformation();

	public:
		TriangleMesh() : Shape(Type::TRIANGLE_MESH) {};
		TriangleMesh(const Utils::Mat4 &transformation, const Processing::MaterialProps &material) : Shape(Type::TRIANGLE_MESH, transformation, material) {};
		void pushVertex(const Utils::Vec3 &vertex);
		void commitTriangle(int v0, int v1, int v2);
		std::optional<float> intersect(const Processing::Ray &ray);
		Utils::Vec3 normalAtPoint(const Utils::Vec3 &point);

	private:
		int vertexCount{ 0 };
		std::vector<Utils::Vec3> normals;
		std::vector<TriIndex> faces;
		std::vector<Utils::Vec3> vertices;
		std::shared_ptr<TriIndex> intersectedFace;
		Processing::BoundingBox boundingBox;
	};
}

#endif // !TRIANGLEMESH_H
