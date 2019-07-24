#include "../Screen.h"

namespace IO
{
	Screen::Screen(int width, int height) : backgroundColor(0.0f, 0.0f, 0.0f)
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

	Utils::ColorTriad Screen::getBackgroundColor() const
	{
		return backgroundColor;
	}

	void Screen::setBackgroundColor(float r, float g, float b)
	{
		Utils::ColorTriad color(r, g, b);
		setBackgroundColor(color);
	}

	void Screen::setBackgroundColor(const Utils::ColorTriad & color)
	{
		backgroundColor = color;
	}
}