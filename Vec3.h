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

};