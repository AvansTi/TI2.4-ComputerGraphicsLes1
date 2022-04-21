#include "Vec3.h"
#include <cmath>

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vec3 Vec3::cross(const Vec3& other)
{
	return Vec3(y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x);
}

float Vec3::dot(const Vec3& other)
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::normalized()
{
	float length = std::sqrt(x * x + y * y + z * z);
	return Vec3(x/length, y/length, z/length);
}
