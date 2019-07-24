#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H
#pragma once

#include <stack>

#include "../Utils/Mat4.h"
#include "../Utils/Vec3.h"

namespace Utils
{
	class TransformMatrix
	{
	public:
		enum class ScaleType
		{
			UNIFORM,
			NON_UNIFORM,
			NONE
		};

		TransformMatrix();
		bool hasTranslation();
		void addTranslation(float tx, float ty, float tz);
		bool hasRotation();
		void addRotation(float degrees, const Vec3 &axis);
		ScaleType getScaleType();
		void addScale(float sx, float sy, float sz);
		void updateBase();
		void resetToBase();
		const Mat4& getMatrix() const;

	private:
		Mat4 operatingMatrix;
		Mat4 baseMatrix;
		bool translated{ false };
		bool rotated{ false };
		ScaleType scaleType{ ScaleType::NONE };
	};
}

#endif // !TRANSFORMMATRIX_H
