#ifndef SAMPLER_H
#define SAMPLER_H
#pragma once

#include "src/Sample.h"

namespace Processing
{
	class Sampler
	{
	public:
		Sampler(int columns, int rows) : columns(columns), rows(rows) {};
		bool hasSample();
		Sample getSample();

	private:
		const int rows;
		const int columns;
		int currentRow = 0;
		int currentColumn = 0;
		bool isDone = false;
	};
}

#endif // !SAMPLER_H
