#ifndef ATTENUATION_H
#define ATTENUATION_H
#pragma once

namespace Processing
{
	class Attenuation
	{
	public:
		Attenuation() {};
		Attenuation(float constant, float linear, float quadratic);
		void setAttenuation(float constant, float linear, float quadratic);
		float getConstant();
		void setConstant(float constant);
		float getLinear();
		void setLinear(float linear);
		float getQuadratic();
		void setQuadratic(float quadratic);

	private:
		float constant;
		float linear;
		float quadratic;
	};
}

#endif // !ATTENUATION_H
