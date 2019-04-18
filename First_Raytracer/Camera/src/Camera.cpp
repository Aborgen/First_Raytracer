#include "../Camera.h"
#include "../../Utils/Operations.h"

namespace Processing
{
	Camera::Camera(Utils::Vec3 eye, Utils::Vec3 center, Utils::Vec3 up, float fovy)
	{
		this->position = eye;
		this->center = center;
		this->fovy = fovy;
		up = setUpVector(up);
		initCoordinateFrame();
	}

	void Camera::initCoordinateFrame()
	{
		using namespace Utils;
		Vec3 delta = position - center;
		Vec3 w = Operations::normalize(delta);
		Vec3 u = Operations::cross(up, w);
		Vec3 normU = Operations::normalize(u);
		Vec3 v = Operations::cross(w, u);
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
}