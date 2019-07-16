#ifndef ATTENUATION_H
#define ATTENUATION_H
#pragma once

#include "../Utils/ColorTriad.h"

namespace Processing
{
	class Attenuation
	{
	public:
		Attenuation() {};
		Attenuation(float constant, float linear, float quadratic);
		Utils::ColorTriad compute(const Utils::ColorTriad &intensity, float distance);
		void setAttenuation(float constant, float linear, float quadratic);
		float getConstant();
		void setConstant(float constant);
		float getLinear();
		void setLinear(float linear);
		float getQuadratic();
		void setQuadratic(float quadratic);

	private:
		float constant{ 1.0f };
		float linear{ 0.0f };
		float quadratic{ 0.0f };
	};
}

#endif // !ATTENUATION_H
