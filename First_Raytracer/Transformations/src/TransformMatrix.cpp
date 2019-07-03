#include "../TransformMatrix.h"

#include "../Transformations.h"
#include "../Utils/Mat3.h"


namespace Utils
{
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
		matrix *= Transformations::translate(tx, ty, tz);
		if (!translated) {
			translated = true;
		}
	}

	void TransformMatrix::addRotation(float degrees, const Vec3 &axis)
	{
		Mat3 rotationMatrix = Transformations::rotate(degrees, axis);
		matrix *= Mat4(
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
		matrix *= Transformations::scale(sx, sy, sz);
		scaleType = (sx == sy && sx == sz && sy == sz) ? ScaleType::UNIFORM : ScaleType::NON_UNIFORM;
	}

	void TransformMatrix::reset()
	{
		translated = false;
		rotated = false;
		scaleType = ScaleType::NONE;
		matrix.identity();
	}

	const Mat4& TransformMatrix::getMatrix() const
	{
		return matrix;
	}
}