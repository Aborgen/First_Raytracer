#include "../Mat3.h"
#include "../Operations.h"
#include "../Vec3.h"

namespace Utils
{
	Mat3::Mat3(
		float ra0, float ra1, float ra2,
		float rb0, float rb1, float rb2,
		float rc0, float rc1, float rc2
	) : Matrix(ra0, ra1, ra2, rb0, rb1, rb2, rc0, rc1, rc2)
	{
		float *row1 = data[0].data();
		row1[0] = ra0;
		row1[1] = ra1;
		row1[2] = ra2;
		float *row2 = data[1].data();
		row2[0] = rb0;
		row2[1] = rb1;
		row2[2] = rb2;
		float *row3 = data[2].data();
		row3[0] = rc0;
		row3[1] = rc1;
		row3[2] = rc2;
	}

	bool Mat3::operator==(const Mat3 &other)
	{
		for (size_t i = 0; i < 3; i++)
		{
			std::array<float, 3> row1 = data[i];
			std::array<float, 3> row2 = other[i];
			for (size_t j = 0; j < 3; j++)
			{
				if (row1[j] != row2[j])
				{
					return false;
				}
			}
		}

		return true;
	}

	bool Mat3::operator!=(const Mat3 &other)
	{
		return !operator==(other);
	}

	Mat3& Mat3::operator+=(const Mat3 &other)
	{
		data[0][0] += other[0][0];
		data[0][1] += other[0][1];
		data[0][2] += other[0][2];
		
		data[1][0] += other[1][0];
		data[1][1] += other[1][1];
		data[1][2] += other[1][2];	

		data[2][0] += other[2][0];
		data[2][1] += other[2][1];
		data[2][2] += other[2][2];

		return *this;
	}

	Mat3 Mat3::operator+(const Mat3 &other)
	{
		Mat3 temp(*this);
		temp += other;
		return temp;
	}

	Mat3& Mat3::operator-=(const Mat3 &other)
	{
		data[0][0] -= other[0][0];
		data[0][1] -= other[0][1];
		data[0][2] -= other[0][2];
		
		data[1][0] -= other[1][0];
		data[1][1] -= other[1][1];
		data[1][2] -= other[1][2];	

		data[2][0] -= other[2][0];
		data[2][1] -= other[2][1];
		data[2][2] -= other[2][2];

		return *this;
	}

	Mat3 Mat3::operator-(const Mat3 &other)
	{
		Mat3 temp(*this);
		temp -= other;
		return temp;
	}

	Mat3& Mat3::operator*=(const Mat3 &other)
	{
		Vec3 row1(data[0][0], data[0][1], data[0][2]);
		Vec3 row2(data[1][0], data[1][1], data[1][2]);
		Vec3 row3(data[2][0], data[2][1], data[2][2]);

		Mat3 otherT = Operations::transpose(other);
		Vec3 column1(otherT[0][0], otherT[0][1], otherT[0][2]);
		Vec3 column2(otherT[1][0], otherT[1][1], otherT[1][2]);
		Vec3 column3(otherT[2][0], otherT[2][1], otherT[2][2]);

		data[0][0] = Operations::dot(row1, column1);
		data[0][1] = Operations::dot(row1, column2);
		data[0][2] = Operations::dot(row1, column3);

		data[1][0] = Operations::dot(row2, column1);
		data[1][1] = Operations::dot(row2, column2);
		data[1][2] = Operations::dot(row2, column3);

		data[2][0] = Operations::dot(row3, column1);
		data[2][1] = Operations::dot(row3, column2);
		data[2][2] = Operations::dot(row3, column3);
		
		return *this;
	}

	Mat3 Mat3::operator*(const Mat3 &other)
	{
		Mat3 temp(*this);
		temp *= other;
		return temp;
	}

	Mat3& Mat3::operator*=(float scalar)
	{
		data[0][0] *= scalar;
		data[0][1] *= scalar;
		data[0][2] *= scalar;

		data[1][0] *= scalar;
		data[1][1] *= scalar;
		data[1][2] *= scalar;

		data[2][0] *= scalar;
		data[2][1] *= scalar;
		data[2][2] *= scalar;

		return *this;
	}

	Mat3 Mat3::operator*(float scalar) const
	{
		Mat3 temp(*this);
		temp *= scalar;
		return temp;
	}

	std::array<float, 3>& Mat3::operator[](int idx)
	{
		if (idx >= data.size())
		{
			throw std::exception("Matrix out of bounds");
		}

		return data[idx];
	}

	std::array<float, 3> Mat3::operator[](int idx) const
	{
		if (idx >= data.size())
		{
			throw std::exception("Matrix out of bounds");
		}

		return data[idx];
	}

	Mat3 operator*(float scalar, const Mat3 &matrix)
	{
		return matrix * scalar;
	}
}
