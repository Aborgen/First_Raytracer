#include "../Transformations.h"
#include "../../Utils/Operations.h"

namespace Utils
{
	Mat4 Transformations::translate(float tx, float ty, float tz)
	{
		Mat4 translationMatrix(
			1.0f, 0.0f, 0.0f, tx,
			0.0f, 1.0f, 0.0f, ty,
			0.0f, 0.0f, 1.0f, tz,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		return translationMatrix;
	}

	Mat3 Transformations::rotate(float degrees, const Vec3 &axis)
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

	Mat4 Transformations::scale(float sx, float sy, float sz)
	{
		Mat4 scaleMatrix(
			sx,   0.0f, 0.0f, 0.0f,
			0.0f, sy,   0.0f, 0.0f,
			0.0f, 0.0f, sz,   0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		return scaleMatrix;
	}

	Vec3 Transformations::extractTranslation(const Mat4 &matrix)
	{
		return Vec3(matrix[0][3], matrix[1][3], matrix[2][3]);
	}

	Mat4 Transformations::extractRotation(const Mat4 &matrix)
	{
		Vec3 scale = extractScale(matrix);
		Mat4 rotationMatrix(matrix);
		rotationMatrix[0][0] /= scale.getX();
		rotationMatrix[1][0] /= scale.getX();
		rotationMatrix[2][0] /= scale.getX();
		rotationMatrix[3][0] = 0.0f;

		rotationMatrix[0][1] /= scale.getY();
		rotationMatrix[1][1] /= scale.getY();
		rotationMatrix[2][1] /= scale.getY();
		rotationMatrix[3][1] = 0.0f;

		rotationMatrix[0][2] /= scale.getZ();
		rotationMatrix[1][2] /= scale.getZ();
		rotationMatrix[2][2] /= scale.getZ();
		rotationMatrix[3][2] = 0.0f;

		rotationMatrix[0][3] = 0.0f;
		rotationMatrix[1][3] = 0.0f;
		rotationMatrix[2][3] = 0.0f;
		rotationMatrix[3][3] = 1.0f;
		return rotationMatrix;
	}

	Vec3 Transformations::extractScale(const Mat4 &matrix)
	{
		float i = Vec3(matrix[0][0], matrix[1][0], matrix[2][0]).length();
		float j = Vec3(matrix[0][1], matrix[1][1], matrix[2][1]).length();
		float k = Vec3(matrix[0][2], matrix[1][2], matrix[2][2]).length();
		return Vec3(i, j, k);
	}
}