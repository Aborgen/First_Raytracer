#include "../Camera.h"
#include "../../Utils/Operations.h"

namespace Visual
{
	Camera::Camera(Utils::Vec3 eye, Utils::Vec3 center, Utils::Vec3 up, float fovy)
	{
		this->eye = eye;
		this->center = center;
		this->up = up;
		this->fovy = fovy;
		initCoordinateFrame();
	}

	void Camera::initCoordinateFrame()
	{
		using namespace Utils;
		Vec3 w = Operations::normalize(eye - center);
		Vec3 u = Operations::normalize(Operations::cross(up, w));
		Vec3 v = Operations::cross(w, u);
		coordinateFrame(
			u.getX(), u.getY(), u.getZ(), -Operations::dot(u, eye),
			v.getX(), v.getY(), v.getZ(), -Operations::dot(v, eye),
			w.getX(), w.getY(), w.getZ(), -Operations::dot(w, eye),
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
}