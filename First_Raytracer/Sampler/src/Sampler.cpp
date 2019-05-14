#include <exception>

#include "../Sampler.h"

namespace Processing
{
	Sampler::Sampler(int columns, int rows)
	{
		this->columns = columns;
		this->rows = rows;
	}

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

		samples++;
		return newSample;
	}
}
