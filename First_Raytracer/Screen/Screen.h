#ifndef SCREEN_H
#define SCREEN_H
#pragma once

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

	private:
		int width;
		int height;
	};
}

#endif // !SCREEN_H
