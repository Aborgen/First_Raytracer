#ifndef SAMPLE_H
#define SAMPLE_H
#pragma once

namespace Processing
{
	class Sample
	{
	public:
		Sample() : x(0), y(0) {}
		Sample(int x, int y) : x(x), y(y) {};
		int getX();
		int getY();

	private:
		const int x;
		const int y;
	};
}

#endif // !SAMPLE_H
