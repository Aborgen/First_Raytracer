#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "../Utils/Mat4.h"
#include "../Utils/Vec3.h"

namespace Processing
{
	class Camera
	{
	public:
		Camera(Utils::Vec3 eye, Utils::Vec3 center, Utils::Vec3 up, float fovy);
		bool takeImage();

	private:
		Utils::Vec3 eye;
		Utils::Vec3 center;
		Utils::Vec3 up;
		Utils::Mat4 coordinateFrame;
		float fovy;
		void initCoordinateFrame();
		Utils::Vec3 setUpVector(const Utils::Vec3 &up);
	};
}

#endif // !CAMERA_H