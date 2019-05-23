#include "../Camera.h"
#include "../../Utils/Operations.h"

namespace Processing
{
	Camera::Camera(Utils::Vec3 eye, Utils::Vec3 center, Utils::Vec3 up, float fovy, IO::Screen screen)
	{
		this->position = eye;
		this->center = center;
		this->fovy = fovy;
		this->up = setUpVector(up);
		this->screen = screen;
		initCoordinateFrame();
	}

	void Camera::initCoordinateFrame()
	{
		using namespace Utils;
		Vec3 delta = position - center;
		Vec3 w = Operations::normalize(delta);
		Vec3 u = Operations::cross(up, w);
		Vec3 normU = Operations::normalize(u);
		Vec3 v = Operations::cross(w, normU);
		coordinateFrame = Mat4(
			normU.getX(), normU.getY(), normU.getZ(), -Operations::dot(normU, position),
			v.getX(),     v.getY(),     v.getZ(),     -Operations::dot(v, position),
			w.getX(),     w.getY(),     w.getZ(),     -Operations::dot(w, position),
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Utils::Vec3 Camera::setUpVector(Utils::Vec3 &up)
	{
		using namespace Utils;
		Vec3 z = position - center;
		Vec3 x = Operations::cross(up, z);
		Vec3 y = Operations::cross(z, x);
		return Operations::normalize(y);
	}

	Ray Camera::castRay(float rasterX, float rasterY)
	{
		using namespace Utils;
		Vec3 direction = generateDirection(rasterX, rasterY);
		return Ray(position, direction);
	}

	//Utils::Vec3 Camera::generateDirection(float rasterX, float rasterY)
	//{
	//	using namespace Utils;
	//	// Normalized device coordinates
	//	float normX = (rasterX + offset) / screen.getWidth();
	//	float normY = (rasterY + offset) / screen.getHeight();
	//	// Screen coordinates
	//	float alpha = Operations::toRadians(fovy / 2);
	//	float fovScaling = tan(fovy / 2);
	//	float screenX = (2 * normX - 1);
	//	float screenY = (1 - 2 * normY);
	//	// Camera space
	//	Vec3 cameraSpace(screenX, screenY, -1.0f);
	//	// Direction, taking into account transformations applied to the camera
	//	Vec3 translatedCameraSpace = Operations::vectorTransform(coordinateFrame, cameraSpace, true);
	//	Vec3 origin = Operations::vectorTransform(coordinateFrame, position, true);
	//	Vec3 direction = translatedCameraSpace - origin;
	//	Vec3 direction2 = cameraSpace;

	//	return Operations::normalize(direction);
	//}

	Utils::Vec3 Camera::generateDirection(float rasterX, float rasterY)
	{
		using namespace Utils;
		float halfWidth = screen.getWidth() / 2.0f;
		float halfHeight = screen.getHeight() / 2.0f;
		float fovx = 2 * atan(tan(fovy * 0.5) * screen.getAspect());
		float alpha = tan(fovx / 2) * ((rasterX - halfWidth) / halfWidth);
		float beta = tan(fovy / 2) * ((halfHeight - rasterY) / halfHeight);
		Vec4 u4 = Vec4(1.0f, 0.0f, 0.0f, 0.0f) * coordinateFrame;
		Vec3 u(u4.getX(), u4.getY(), u4.getZ());
		Vec4 v4 = Vec4(0.0f, 1.0f, 0.0f, 0.0f) * coordinateFrame;
		Vec3 v(v4.getX(), v4.getY(), v4.getZ());
		Vec4 w4 = Vec4(0.0f, 0.0f, 1.0f, 0.0f) * coordinateFrame;
		Vec3 w(w4.getX(), w4.getY(), w4.getZ());
		Vec3 direction = (alpha * u) + (beta * v) - w;
		return Operations::normalize(direction);
	}
}