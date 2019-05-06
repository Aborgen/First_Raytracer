#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "../Utils/Mat4.h"
#include "../Utils/Vec3.h"
#include "../Raytracer/RayCapable.h"
#include "../Screen/Screen.h"

namespace Processing
{
	class Camera : public RayCapable
	{
	public:
		Camera() {}
		Camera(Utils::Vec3 eye, Utils::Vec3 center, Utils::Vec3 up, float fovy, IO::Screen screen);
		Ray castRay(float rasterX, float rasterY);

	private:
		Utils::Vec3 center;
		Utils::Vec3 up;
		Utils::Mat4 coordinateFrame;
		float fovy;
		float offset = 0.5f; // Ensures that we cast ray toward the center of each pixel
		IO::Screen screen;
		void initCoordinateFrame();
		Utils::Vec3 setUpVector(Utils::Vec3 &up);
		Utils::Vec3 generateDirection(float rasterX, float rasterY);
	};
}

#endif // !CAMERA_H