#ifndef SAMPLER_H
#define SAMPLER_H
#pragma once

#include "src/Sample.h"

namespace Processing
{
	class Sampler
	{
	public:
		Sampler() {}
		Sampler(int columns, int rows);
		bool hasSample();
		Sample getSample();

	private:
		int rows;
		int columns;
		int currentRow = 0;
		int currentColumn = 0;
		bool isDone = false;
	};
}

#endif // !SAMPLER_H
