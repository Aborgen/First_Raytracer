#ifndef VECTOR_H
#define VECTOR_H
#pragma once

#include "Coordinates.h"

namespace Utils
{
	class Vector : public Coordinates
	{
	public:
		int length();
		operator==(const Vector &other);
		operator!=(const Vector &other);
		operator+(const Vector &other);
		operator-(const Vector &other);

	private:

	};
}

#endif // !VECTOR_H