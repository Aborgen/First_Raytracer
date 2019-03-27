#ifndef VEC4_H
#define VEC4_H
#pragma once

namespace Utils
{
	class Vec4
	{
	public:
		Vec4();
		float getW();
		void setW(float w);

	private:
		float w;
	};
}

#endif // !VEC4_H