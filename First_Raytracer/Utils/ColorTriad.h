#ifndef COLORTRIAD_H
#define COLORTRIAD_H
#pragma once

namespace Utils
{
	class ColorTriad
	{
	public:
		ColorTriad(float r, float g, float b);
		float getR();
		void setR(float r);
		float getG();
		void setG(float g);
		float getB();
		void setB(float b);

	private:
		float r;
		float g;
		float b;
	};
}

#endif // !COLORTRIAD_H
