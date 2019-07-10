#include "../TransformMatrix.h"

#include "../Transformations.h"
#include "../Utils/Mat3.h"


namespace Utils
{
	TransformMatrix::TransformMatrix()
	{
		baseMatrix.identity();
		operatingMatrix = baseMatrix;
	}

	bool TransformMatrix::hasTranslation()
	{
		return translated;
	}

	bool TransformMatrix::hasRotation()
	{
		return rotated;
	}

	TransformMatrix::ScaleType TransformMatrix::getScaleType()
	{
		return scaleType;
	}

	void TransformMatrix::addTranslation(float tx, float ty, float tz)
	{
		operatingMatrix *= Transformations::translate(tx, ty, tz);
		if (!translated) {
			translated = true;
		}
	}

	void TransformMatrix::addRotation(float degrees, const Vec3 &axis)
	{
		Mat3 rotationMatrix = Transformations::rotate(degrees, axis);
		operatingMatrix *= Mat4(
			rotationMatrix[0][0], rotationMatrix[0][1], rotationMatrix[0][2], 0.0f,
			rotationMatrix[1][0], rotationMatrix[1][1], rotationMatrix[1][2], 0.0f,
			rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		if (!rotated) {
			rotated = true;
		}
	}

	void TransformMatrix::addScale(float sx, float sy, float sz)
	{
		operatingMatrix *= Transformations::scale(sx, sy, sz);
		scaleType = (sx == sy && sx == sz && sy == sz) ? ScaleType::UNIFORM : ScaleType::NON_UNIFORM;
	}

	void TransformMatrix::updateBase()
	{
		baseMatrix = operatingMatrix;
	}

	void TransformMatrix::resetToBase()
	{
		operatingMatrix = baseMatrix;
		translated = Transformations::extractTranslation(operatingMatrix) != Vec3(0.0f, 0.0f, 0.0f);
		rotated = Transformations::extractRotation(operatingMatrix) != Mat4().identity();

		Vec3 scale = Transformations::extractScale(operatingMatrix);
		if (scale == Vec3(1.0f, 1.0f, 1.0f)) {
			scaleType == ScaleType::NONE;
		}
		else if (scale.getX() == scale.getY() && scale.getX() == scale.getZ() && scale.getY() == scale.getZ()) {
			scaleType == ScaleType::UNIFORM;
		}
		else {
			scaleType == ScaleType::NON_UNIFORM;
		}
	}

	const Mat4& TransformMatrix::getMatrix() const
	{
		return operatingMatrix;
	}
}