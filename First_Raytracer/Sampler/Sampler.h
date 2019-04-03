#ifndef SAMPLER_H
#define SAMPLER_H
#pragma once

#include <optional>

#include "src/Sample.h"

namespace Processing
{
	class Sampler
	{
	public:
		Sampler();
		bool hasSample();
		std::optional<Sample> Sampler::getSample();

	private:
		bool lastSampleGiven = false;
	};
}

#endif // !SAMPLER_H
