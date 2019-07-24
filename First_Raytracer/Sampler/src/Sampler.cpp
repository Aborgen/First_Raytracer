#include <exception>

#include "../Sampler.h"

namespace Processing
{
	bool Sampler::hasSample()
	{
		return progress != Progress::FINISH;
	}

	Sample Sampler::getSample()
	{
		if (progress == Progress::FINISH)
		{
			throw new std::exception("There are no more sample to be taken. Use hasSample to protect against this.");
		}

		Sample newSample(currentColumn, currentRow);
		if (currentColumn == columns) {
			if (currentRow != rows) {
				currentColumn = 1;
				currentRow++;
			}
		}
		else {
			currentColumn++;
		}

		samples++;
		trackProgress();
		return newSample;
	}

	Sampler::Progress Sampler::getProgress()
	{
		return progress;
	}

	void Sampler::trackProgress()
	{
		if (samples == finalSample * 0.25) {
			progress = Progress::FOURTH;
		}
		else if (samples == finalSample * 0.50) {
			progress = Progress::HALF;
		}
		else if (samples == finalSample * 0.75) {
			progress = Progress::THREE_FOURTHS;
		}
		else if (samples == finalSample) {
			progress = Progress::FINISH;
		}
		else {
			progress = Progress::NO_MILESTONE;
		}
	}
}
