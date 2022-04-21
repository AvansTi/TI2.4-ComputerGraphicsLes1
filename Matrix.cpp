#include "Matrix.h"
#include <cmath>

Mat4::Mat4()
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			data[x + 4 * y] = x == y ? 1.0f : 0.0f;
}

Mat4 Mat4::identity()
{
	return Mat4();
}

Mat4 Mat4::translate(const Vec3& position)
{
	Mat4 mat;
	mat.el(3, 0) = position.x;
	mat.el(3, 1) = position.y;
	mat.el(3, 2) = position.z;
	return mat;
}

Mat4 Mat4::scale(const Vec3& position)
{
	Mat4 mat;
	mat.el(0, 0) = position.x;
	mat.el(1, 1) = position.y;
	mat.el(2, 2) = position.z;
	return mat;
}

Mat4 Mat4::perspective(float fov, float aspect, float zNear, float zFar)
{
	Mat4 m;
	float tanHalfFov = (float)std::tan(fov / 2);

	m.el(0, 0) = 1 / (aspect * tanHalfFov);
	m.el(1, 1) = 1 / tanHalfFov;
	m.el(2, 2) = -(zFar + zNear) / (zFar - zNear);
	m.el(2, 3) = -1;
	m.el(3, 2) = -(2 * zFar * zNear) / (zFar - zNear);
	return m;
}

Mat4 Mat4::rotation(float angle, Vec3 axis)
{
	Mat4 m;
	float a = angle;
	float c = (float)std::cos(a);
	float s = (float)std::sin(a);

	axis = axis.normalized();

	Vec3 temp = axis * (1 - c);

	m.el(0, 0) = c + temp.x * axis.x;
	m.el(0, 1) = 0 + temp.x * axis.y + s * axis.z;
	m.el(0, 2) = 0 + temp.x * axis.z - s * axis.y;

	m.el(1, 0) = 0 + temp.y * axis.x - s * axis.z;
	m.el(1, 1) = c + temp.y * axis.y;
	m.el(1, 2) = 0 + temp.y * axis.z + s * axis.x;

	m.el(2, 0) = 0 + temp.z * axis.x + s * axis.y;
	m.el(2, 1) = 0 + temp.z * axis.y - s * axis.x;
	m.el(2, 2) = c + temp.z * axis.z;
	m.el(3, 3) = 1;
	return m;
}
