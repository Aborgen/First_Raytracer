#ifndef MATERIALPROPS_H
#define MATERIALPROPS_H
#pragma once

#include "../Utils/ColorTriad.h"

namespace Processing
{
	class MaterialProps
	{
	public:
		Utils::ColorTriad getAmbient() const;
		void setAmbient(float r, float g, float b);
		Utils::ColorTriad getEmission() const;
		void setEmission(float r, float g, float b);
		Utils::ColorTriad getDiffuse() const;
		void setDiffuse(float r, float g, float b);
		Utils::ColorTriad getSpecular() const;
		void setSpecular(float r, float g, float b);
		float getShininess() const;
		void setShininess(float intensity);

	private:
		Utils::ColorTriad ambient = Utils::ColorTriad(0, 0, 0);
		Utils::ColorTriad emission = Utils::ColorTriad(0, 0, 0);
		Utils::ColorTriad diffuse = Utils::ColorTriad(0, 0, 0);
		Utils::ColorTriad specular = Utils::ColorTriad(0, 0, 0);
		float shininess = 0;
	};
}

#endif // !MATERIALPROPS_H
