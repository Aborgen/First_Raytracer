#ifndef TRANSFORMATION_H
#pragma once

#include "../Utils/Mat3.h";
#include "../Utils/Mat4.h";
#include "../Utils/Vec3.h";

namespace Processing
{
	class Transformations
	{
	public:
		static Utils::Mat4 translate(float tx, float ty, float tz);
		static Utils::Mat3 rotate(float degrees, Utils::Vec3 &axis);
		static Utils::Mat4 scale(float sx, float sy, float sz);

	private:
		Transformations() {}
	};
}

#endif // !TRANSFORMATION_H
