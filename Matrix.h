#pragma once

#include "Vec3.h"

class Mat4
{
public:
	float data[4 * 4];

	Mat4();
	inline float& el(int x, int y)
	{
		return data[x + 4 * y];
	}
	inline const float& el(int x, int y) const
	{
		return data[x + 4 * y];
	}

	static Mat4 identity();

	static Mat4 translate(const Vec3& position);
	static Mat4 scale(const Vec3& position);
	static Mat4 perspective(float fov, float aspect, float zNear, float zFar);


	static Mat4 rotation(float angle, Vec3 axis);

	Vec3 operator *(const Vec3 &vec)
	{
		return Vec3(
			el(0, 0) * vec.x + el(0, 1) * vec.y + el(0, 2) * vec.z + el(0, 3),
			el(1, 0) * vec.x + el(1, 1) * vec.y + el(1, 2) * vec.z + el(1, 3),
			el(2, 0) * vec.x + el(2, 1) * vec.y + el(2, 2) * vec.z + el(2, 3)
		);
	}
	Mat4 operator *(const Mat4 &mat2) const
	{
		Mat4 ret;

		for (int i = 0; i < 4; i++)
			for (int ii = 0; ii < 4; ii++)
				ret.el(i, ii) = 
					el(i, 0) * mat2.el(0, ii) +
					el(i, 1) * mat2.el(1, ii) +
					el(i, 2) * mat2.el(2, ii) +
					el(i, 3) * mat2.el(3, ii);

		return ret;
	}

};