#ifndef MATERIALPROPS_H
#define MATERIALPROPS_H
#pragma once

#include "../../Utils/ColorTriad.h"

namespace Processing
{
	class MaterialProps
	{
	public:
		Utils::ColorTriad getEmission();
		void setEmission(float r, float g, float b);
		Utils::ColorTriad getDiffuse();
		void setDiffuse(float r, float g, float b);
		Utils::ColorTriad getSpecular();
		void setSpecular(float r, float g, float b);
		float getShininess();
		void setShininess(float intensity);

	private:
		Utils::ColorTriad emission = Utils::ColorTriad(0, 0, 0);
		Utils::ColorTriad diffuse = Utils::ColorTriad(0, 0, 0);
		Utils::ColorTriad specular = Utils::ColorTriad(0, 0, 0);
		float shininess = 0;
	};
}

#endif // !MATERIALPROPS_H
