#include "../Mat4.h"
#include "../Operations.h"
#include "../Vec4.h"

namespace Utils
{
	Mat4::Mat4(
		float ra0, float ra1, float ra2, float ra3,
		float rb0, float rb1, float rb2, float rb3,
		float rc0, float rc1, float rc2, float rc3,
		float rd0, float rd1, float rd2, float rd3
	) : Matrix(ra0, ra1, ra2, ra3, rb0, rb1, rb2, rb3, rc0, rc1, rc2, rc3, rd0, rd1, rd2, rd3)
	{
		float *row1 = data[0].data();
		row1[0] = ra0;
		row1[1] = ra1;
		row1[2] = ra2;
		row1[3] = ra3;
		float *row2 = data[1].data();
		row2[0] = rb0;
		row2[1] = rb1;
		row2[2] = rb2;
		row2[3] = rb3;
		float *row3 = data[2].data();
		row3[0] = rc0;
		row3[1] = rc1;
		row3[2] = rc2;
		row3[3] = rc3;
		float *row4 = data[3].data();
		row4[0] = rd0;
		row4[1] = rd1;
		row4[2] = rd2;
		row4[3] = rd3;
	}

	Mat4& Mat4::identity()
	{
		float *row1 = data[0].data();
		row1[0] = 1.0f;
		row1[1] = 0.0f;
		row1[2] = 0.0f;
		row1[3] = 0.0f;
		float *row2 = data[1].data();
		row2[0] = 0.0f;
		row2[1] = 1.0f;
		row2[2] = 0.0f;
		row2[3] = 0.0f;
		float *row3 = data[2].data();
		row3[0] = 0.0f;
		row3[1] = 0.0f;
		row3[2] = 1.0f;
		row3[3] = 0.0f;
		float *row4 = data[3].data();
		row4[0] = 0.0f;
		row4[1] = 0.0f;
		row4[2] = 0.0f;
		row4[3] = 1.0f;

		return *this;
	}

	bool Mat4::operator==(const Mat4 &other)
	{
		for (size_t i = 0; i < 4; i++)
		{
			std::array<float, 4> row1 = data[i];
			std::array<float, 4> row2 = other[i];
			for (size_t j = 0; j < 4; j++)
			{
				if (row1[j] != row2[j])
				{
					return false;
				}
			}
		}

		return true;
	}

	bool Mat4::operator!=(const Mat4 &other)
	{
		return !operator==(other);
	}

	Mat4& Mat4::operator+=(const Mat4 &other)
	{
		data[0][0] += other[0][0];
		data[0][1] += other[0][1];
		data[0][2] += other[0][2];
		data[0][3] += other[0][3];
		
		data[1][0] += other[1][0];
		data[1][1] += other[1][1];
		data[1][2] += other[1][2];	
		data[1][3] += other[1][3];

		data[2][0] += other[2][0];
		data[2][1] += other[2][1];
		data[2][2] += other[2][2];
		data[2][3] += other[2][3];

		data[3][0] += other[3][0];
		data[3][1] += other[3][1];
		data[3][2] += other[3][2];
		data[3][3] += other[3][3];

		return *this;
	}

	Mat4 Mat4::operator+(const Mat4 &other)
	{
		Mat4 temp(*this);
		temp += other;
		return temp;
	}

	Mat4& Mat4::operator-=(const Mat4 &other)
	{
		data[0][0] -= other[0][0];
		data[0][1] -= other[0][1];
		data[0][2] -= other[0][2];
		data[0][3] -= other[0][3];

		data[1][0] -= other[1][0];
		data[1][1] -= other[1][1];
		data[1][2] -= other[1][2];
		data[1][3] -= other[1][3];

		data[2][0] -= other[2][0];
		data[2][1] -= other[2][1];
		data[2][2] -= other[2][2];
		data[2][3] -= other[2][3];

		data[3][0] -= other[3][0];
		data[3][1] -= other[3][1];
		data[3][2] -= other[3][2];
		data[3][3] -= other[3][3];

		return *this;
	}

	Mat4 Mat4::operator-(const Mat4 &other)
	{
		Mat4 temp(*this);
		temp -= other;
		return temp;
	}

	Mat4& Mat4::operator*=(const Mat4 &other)
	{
		Vec4 row1(data[0][0], data[0][1], data[0][2], data[0][3]);
		Vec4 row2(data[1][0], data[1][1], data[1][2], data[1][3]);
		Vec4 row3(data[2][0], data[2][1], data[2][2], data[2][3]);
		Vec4 row4(data[3][0], data[3][1], data[3][2], data[3][3]);

		Mat4 otherT = Operations::transpose(other);
		Vec4 column1(otherT[0][0], otherT[0][1], otherT[0][2], otherT[0][3]);
		Vec4 column2(otherT[1][0], otherT[1][1], otherT[1][2], otherT[1][3]);
		Vec4 column3(otherT[2][0], otherT[2][1], otherT[2][2], otherT[2][3]);
		Vec4 column4(otherT[3][0], otherT[3][1], otherT[3][2], otherT[3][3]);

		data[0][0] = Operations::dot(row1, column1);
		data[0][1] = Operations::dot(row1, column2);
		data[0][2] = Operations::dot(row1, column3);
		data[0][3] = Operations::dot(row1, column4);

		data[1][0] = Operations::dot(row2, column1);
		data[1][1] = Operations::dot(row2, column2);
		data[1][2] = Operations::dot(row2, column3);
		data[1][3] = Operations::dot(row2, column4);

		data[2][0] = Operations::dot(row3, column1);
		data[2][1] = Operations::dot(row3, column2);
		data[2][2] = Operations::dot(row3, column3);
		data[2][3] = Operations::dot(row3, column4);

		data[3][0] = Operations::dot(row4, column1);
		data[3][1] = Operations::dot(row4, column2);
		data[3][2] = Operations::dot(row4, column3);
		data[3][3] = Operations::dot(row4, column4);
		
		return *this;
	}

	Mat4 Mat4::operator*(const Mat4 &other)
	{
		Mat4 temp(*this);
		temp *= other;
		return temp;
	}

	Vec4 Mat4::operator*(const Vec4 &vector) const
	{
		Vec4 column1 = Vec4(data[0][0], data[1][0], data[2][0], data[3][0]) * vector.getX();
		Vec4 column2 = Vec4(data[0][1], data[1][1], data[2][1], data[3][1]) * vector.getY();
		Vec4 column3 = Vec4(data[0][2], data[1][2], data[2][2], data[3][2]) * vector.getZ();
		Vec4 column4 = Vec4(data[0][3], data[1][3], data[2][3], data[3][3]) * vector.getW();

		Vec4 newVector = column1 + column2 + column3 + column4;
		return newVector;
	}

	std::array<float, 4>& Mat4::operator[](int idx)
	{
		if (idx >= data.size())
		{
			throw std::exception("Matrix out of bounds");
		}

		return data[idx];
	}

	std::array<float, 4> Mat4::operator[](int idx) const
	{
		if (idx >= data.size())
		{
			throw std::exception("Matrix out of bounds");
		}

		return data[idx];
	}
	
	// Row multiplication
	Vec4 operator*(const Vec4 &vector, const Mat4 &matrix)
	{
		Vec4 row1(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
		Vec4 row2(matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
		Vec4 row3(matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
		Vec4 row4(matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);

		return (row1 * vector.getX()) + (row2 * vector.getY()) + (row3 * vector.getZ()) + (row4 * vector.getW());
	}
}