#ifndef SAMPLE_H
#define SAMPLE_H
#pragma once

namespace Processing
{
	class Sample
	{
	public:
		Sample() : x(0.0f), y(0.0f) {}
		Sample(float x, float y) : x(x), y(y) {};
		float getX();
		float getY();

	private:
		const float x;
		const float y;
	};
}

#endif // !SAMPLE_H
