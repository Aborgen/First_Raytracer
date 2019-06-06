#ifndef SCREEN_H
#define SCREEN_H
#pragma once

#include "../Utils/ColorTriad.h"

namespace IO
{
	class Screen
	{
	public:
		Screen() {}
		Screen(int width, int height);
		int getWidth();
		int getHeight();
		float getAspect();
		Utils::ColorTriad getBackgroundColor() const;
		void setBackgroundColor(float r, float g, float b);
		void setBackgroundColor(const Utils::ColorTriad &color);

	private:
		int width;
		int height;
		Utils::ColorTriad backgroundColor;
	};
}

#endif // !SCREEN_H
