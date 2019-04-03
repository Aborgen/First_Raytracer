#ifndef SAMPLE_H
#define SAMPLE_H
#pragma once

namespace Processing
{
	class Sample
	{
	public:
		Sample(float x, float y);
		float getX();
		void setX(float x);
		float getY();
		void setY(float y);

	private:
		float x;
		float y;
	};
}

#endif // !SAMPLE_H
