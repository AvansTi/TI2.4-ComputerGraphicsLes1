#pragma once

class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
		float data[3];
	};

	Vec3(float x, float y, float z);

	Vec3 cross(const Vec3& other);
	float dot(const Vec3& other);

	Vec3 normalized();

	Vec3 operator * (float f)
	{
		return Vec3(x * f, y * f, z * f);
	}

	Vec3 operator + (const Vec3 &other)
	{
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

};