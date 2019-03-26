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
		//mat4 transformationMatrix(
		//	u.x,  u.y,  u.z,  -glm::dot(u, eye),
		//	v.x,  v.y,  v.z,  -glm::dot(v, eye),
		//	w.x,  w.y,  w.z,  -glm::dot(w, eye),
		//	0.0f, 0.0f, 0.0f, 1.0f
		//);

		//transformationMatrix = glm::transpose(transformationMatrix);
		//return transformationMatrix;
	}
}