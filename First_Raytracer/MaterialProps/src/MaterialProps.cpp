#include "MaterialProps.h"

namespace Processing
{
	Utils::ColorTriad MaterialProps::getAmbient()
	{
		return ambient;
	}

	void MaterialProps::setAmbient(float r, float g, float b)
	{
		Utils::ColorTriad ambient(r, g, b);
		this->ambient = ambient;

	}
	
	Utils::ColorTriad MaterialProps::getEmission()
	{
		return emission;
	}

	void MaterialProps::setEmission(float r, float g, float b)
	{
		Utils::ColorTriad emission(r, g, b);
		this->emission = emission;

	}

	Utils::ColorTriad MaterialProps::getDiffuse()
	{
		return diffuse;
	}

	void MaterialProps::setDiffuse(float r, float g, float b)
	{
		Utils::ColorTriad diffuse(r, g, b);
		this->diffuse = diffuse;
	}

	Utils::ColorTriad MaterialProps::getSpecular()
	{
		return specular;
	}

	void MaterialProps::setSpecular(float r, float g, float b)
	{
		Utils::ColorTriad specular(r, g, b);
		this->specular = specular;
	}

	float MaterialProps::getShininess()
	{
		return shininess;
	}

	void MaterialProps::setShininess(float intensity)
	{
		shininess = intensity;
	}
}