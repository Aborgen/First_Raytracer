#ifndef SAMPLER_H
#define SAMPLER_H
#pragma once

#include "src/Sample.h"

namespace Processing
{
	class Sampler
	{
	public:
		enum class Progress
		{
			INIT,
			FOURTH,
			HALF,
			THREE_FOURTHS,
			FINISH,
			NO_MILESTONE
		};

		Sampler() {}
		Sampler(int columns, int rows) : columns(columns), rows(rows), finalSample(columns * rows) {};
		bool hasSample();
		Sample getSample();
		Progress getProgress();

	private:
		Progress progress{ Progress::INIT };
		int rows;
		int columns;
		int finalSample;
		int samples{ 0 };
		int currentRow{ 1 };
		int currentColumn{ 1 };
		void trackProgress();
	};
}

#endif // !SAMPLER_H
