#include "../Camera.h"
#include "../../Utils/Operations.h"

namespace Processing
{
	Camera::Camera(Utils::Vec3 eye, Utils::Vec3 center, Utils::Vec3 up, float fovy, IO::Screen screen)
	{
		this->position = eye;
		this->center = center;
		this->fovy = fovy;
		this->fovx = 2 * atan(tan(fovy * 0.5) * screen.getAspect());
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

	Utils::Vec3 Camera::generateDirection(float rasterX, float rasterY)
	{
		using namespace Utils;
		float halfWidth = screen.getWidth() / 2.0f;
		float halfHeight = screen.getHeight() / 2.0f;
		float alpha = tan(fovx / 2) * ((rasterX - halfWidth) / halfWidth);
		float beta = tan(fovy / 2) * ((halfHeight - rasterY) / halfHeight);
		// Direction is given as alpha * u + beta * v - w;
		// u, v, and w correspond to rows 0, 1, and 2 of coordinateFrame.
		// In other words, we want alpha of row 0, beta of row 1, and -1 of row 2.
		// If we transpose coordinateFrame, this becomes simple matrix-column multiplication.
		// Note: vectorTransform simply tacks on a homogenous coordinate -- changing the given Vec3 to a Vec4 --
		// making it possible to multiply with the given Mat4.
		Mat4 frameT = Operations::transpose(coordinateFrame);
		Vec3 quantities(alpha, beta, -1.0f);
		Vec3 direction = Operations::vectorTransform(frameT, quantities);
		return Operations::normalize(direction);
	}
}