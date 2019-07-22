#include "../Shape.h"
#include "../Utils/Operations.h"

namespace Geometry
{
	Shape::Type Shape::getType()
	{
		return type;
	}

	Processing::MaterialProps Shape::getMaterial()
	{
		return material;
	}

	void Shape::setMaterial(const Processing::MaterialProps &material)
	{
		this->material = material;
	}

	void Shape::setAmbient(float r, float g, float b)
	{
		material.setAmbient(r, g, b);
	}

	void Shape::setEmission(float r, float g, float b)
	{
		material.setEmission(r, g, b);
	}

	void Shape::setDiffuse(float r, float g, float b)
	{
		material.setDiffuse(r, g, b);
	}

	void Shape::setSpecular(float r, float g, float b)
	{
		material.setSpecular(r, g, b);
	}

	void Shape::setShinniness(float intensity)
	{
		material.setShininess(intensity);
	}

	void Shape::setNormalTransformation()
	{
		std::optional<Utils::Mat4> matrixInverse = Utils::Operations::inverse(transformation);
		if (matrixInverse.has_value()) {
			normalTransformation = Utils::Operations::transpose(matrixInverse.value());
		}
	}
}