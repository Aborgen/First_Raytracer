#include <algorithm>

#include "Attenuation.h"

namespace Processing
{
	Attenuation::Attenuation(float constant, float linear, float quadratic)
	{
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	Utils::ColorTriad Attenuation::compute(const Utils::ColorTriad &intensity, float distance)
	{
		float distance2 = distance * distance;
		float denominator = (constant + linear * distance + quadratic * distance2);
		return intensity / denominator;
	}

	void Attenuation::setAttenuation(float constant, float linear, float quadratic)
	{
		setConstant(constant);
		setLinear(linear);
		setQuadratic(quadratic);
	}

	float Attenuation::getConstant()
	{
		return constant;
	}

	void Attenuation::setConstant(float constant)
	{
		this->constant = std::max(constant, 0.0f);
	}

	float Attenuation::getLinear()
	{
		return linear;
	}

	void Attenuation::setLinear(float linear)
	{
		this->linear = std::max(linear, 0.0f);
	}

	float Attenuation::getQuadratic()
	{
		return quadratic;
	}

	void Attenuation::setQuadratic(float quadratic)
	{
		this->quadratic = std::max(quadratic, 0.0f);
	}
}