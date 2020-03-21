#include "Vec2i.h"

namespace Core {

Vec2i::Vec2i()
	:
	x(0),
	y(0)
{ }

Vec2i::Vec2i(int x, int y) 
	:
	x(x),
	y(y)
{ }

Vec2i operator + (const Vec2i& lhs, const Vec2i& rhs)
{
	return Vec2i(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vec2i operator - (const Vec2i& lhs, const Vec2i& rhs)
{
	return Vec2i(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vec2i operator - (const Vec2i& vec)
{
	return vec * -1;
}

Vec2i operator * (const Vec2i& vec, int value)
{
	return Vec2i(vec.x * value, vec.y * value);
}

Vec2 operator / (const Vec2i& vec, float value)
{
	return Vec2i(vec.x / value, vec.y / value);
}


Vec2i& Vec2i::operator += (const Vec2i& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2i& Vec2i::operator -= (const Vec2i& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2i& Vec2i::operator *= (int value)
{
	x *= value;
	y *= value;
	return *this;
}

} // namespace Core