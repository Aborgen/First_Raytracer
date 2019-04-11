#include <exception>

#include "../Sampler.h"

namespace Processing
{
	bool Sampler::hasSample()
	{
		return !isDone;
	}

	Sample Sampler::getSample()
	{
		if (isDone)
		{
			throw new std::exception("There are no more sample to be taken. Use hasSample to protect against this.");
		}

		Sample newSample = Sample(currentColumn, currentRow);
		if (currentColumn == columns) {
			if (currentRow == rows) {
				isDone = true;
			}
			else {
				currentColumn = 0;
				currentRow++;
			}
		}
		else {
			currentColumn++;
		}

		return newSample;
	}
}
