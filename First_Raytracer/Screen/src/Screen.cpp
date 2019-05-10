#include "../Screen.h"

namespace IO
{
	Screen::Screen(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	int Screen::getWidth()
	{
		return width;
	}

	int Screen::getHeight()
	{
		return height;
	}

	float Screen::getAspect()
	{
		return width / (float) height;
	}
}