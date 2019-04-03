#include <exception>

#include "../Sampler.h"

namespace Processing
{
	bool Sampler::hasSample()
	{
		// summthin'
		return true;
	}

	std::optional<Sample> Sampler::getSample()
	{
		if (lastSampleGiven)
		{
			return std::nullopt;
		}

		return Sample(0.0f, 0.0f);
	}
}