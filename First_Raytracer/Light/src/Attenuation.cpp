#include "Attenuation.h"

namespace Processing
{
	Attenuation::Attenuation(float constant, float linear, float quadratic)
	{
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	float Attenuation::getConstant()
	{
		return constant;
	}

	void Attenuation::setConstant(float constant)
	{
		this->constant = constant;
	}

	float Attenuation::getLinear()
	{
		return linear;
	}

	void Attenuation::setLinear(float linear)
	{
		this->linear = linear;
	}

	float Attenuation::getQuadratic()
	{
		return quadratic;
	}

	void Attenuation::setQuadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}
}