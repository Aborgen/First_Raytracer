#include "../Transformations.h"
#include "../../Utils/Operations.h"

namespace Processing
{
	Utils::Mat4 Transformations::translate(float tx, float ty, float tz)
	{
		Utils::Mat4 translationMatrix(
			1.0f, 0.0f, 0.0f, tx,
			0.0f, 1.0f, 0.0f, ty,
			0.0f, 0.0f, 1.0f, tz,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		return translationMatrix;
	}

	Utils::Mat3 Transformations::rotate(float degrees, Utils::Vec3 &axis)
	{
		using namespace Utils;
		Vec3 axisOfRotation = Operations::normalize(axis);
		float normX = axisOfRotation.getX();
		float normY = axisOfRotation.getY();
		float normZ = axisOfRotation.getZ();
		Mat3 dualMatrix(
			0.0f, -normZ, normY,
			normZ, 0.0f, -normX,
			-normY, normX, 0.0f
		);

		float theta = Operations::toRadians(degrees);
		float cosineOfTheta = cos(theta);
		float sineOfTheta = sin(theta);
		Mat3 identity(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);

		Mat3 scalarMatrix = identity * cosineOfTheta;
		Mat3 axisParallel = Operations::outerProduct(axisOfRotation, axisOfRotation) * (1 - cosineOfTheta);
		Mat3 axisPerpendicular = dualMatrix * sineOfTheta;
		Mat3 rotationMatrix = scalarMatrix + axisParallel + axisPerpendicular;

		return rotationMatrix;
	}

	Utils::Mat4 Transformations::scale(float sx, float sy, float sz)
	{
		Utils::Mat4 scaleMatrix(
			sx,   0.0f, 0.0f, 0.0f,
			0.0f, sy,   0.0f, 0.0f,
			0.0f, 0.0f, sz,   0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		return scaleMatrix;
	}

}