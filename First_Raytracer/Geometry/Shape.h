#ifndef SHAPE_H
#define SHAPE_H
#pragma once

#include <optional>

#include "../MaterialProps/MaterialProps.h"
#include "../Utils/Mat4.h"
#include "../Ray/Ray.h"

namespace Geometry
{
	class Shape
	{
	public:
		enum Type
		{
			SPHERE,
			TRIANGLE,
			TRIANGLE_MESH
		};

		virtual std::optional<float> intersect(const Processing::Ray &ray) = 0;
		virtual Utils::Vec3 normalAtPoint(const Utils::Vec3 &point) = 0;
		Type getType();
		Processing::MaterialProps getMaterial();
		void setMaterial(Processing::MaterialProps material);
		void setAmbient(float r, float g, float b);
		void setEmission(float r, float g, float b);
		void setDiffuse(float r, float g, float b);
		void setSpecular(float r, float g, float b);
		void setShinniness(float intensity);
		virtual ~Shape() {}

	protected:
		Shape(Type type) : type(type) { transformation.identity(); };
		Shape(Type type, const Utils::Mat4 &transformation) : type(type), transformation(transformation) {};
		Shape(Type type, const Utils::Mat4 &transformation, const Processing::MaterialProps &material) : type(type), transformation(transformation), material(material) {};
		const Type type;
		Utils::Mat4 transformation;
		Processing::MaterialProps material;
	};
}

#endif // !SHAPE_H
