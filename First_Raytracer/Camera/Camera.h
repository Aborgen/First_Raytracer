#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "../Utils/Vec3.h"

namespace Visual
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
		float fovy;
		initCoordinateFrame();
	};
}

#endif // !CAMERA_H