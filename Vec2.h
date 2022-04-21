#pragma once

class Vec2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};

	Vec2(float x, float y);

	Vec2 operator * (float v);
	Vec2 operator + (const Vec2& other);
};