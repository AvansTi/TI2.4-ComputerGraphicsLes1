#include "Vec2.h"

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

Vec2 Vec2::operator*(float v)
{
	return Vec2(x*v, y*v);
}

Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(x+other.x, y+other.y);
}
