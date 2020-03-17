#include "Vec2.h"
#include "Vec2i.h"

namespace Core {
Vec2::Vec2()
	:
	x(0.0f),
	y(0.0f)
{ }

Vec2::Vec2(float x, float y)
	:
	x(x),
	y(y)
{ }

Vec2::Vec2(const Vec2i& vec2i)
	:
	x((float)vec2i.x),
	y((float)vec2i.y)
{ }

Vec2 operator + (const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vec2 operator - (const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vec2 operator - (const Vec2& vec)
{
	return vec * -1;
}

Vec2  operator * (const Vec2& vec, float value) 
{
	return Vec2(vec.x * value, vec.y * value);
}

Vec2  operator / (const Vec2& vec, float value)
{
	return Vec2(vec.x / value, vec.y / value);
}


Vec2 operator - (const Vec2& vec, float val)
{
	return Vec2(vec.x - val, vec.y - val);
}

Vec2& Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2& Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2& Vec2::operator *= (float value)
{
	x *= value;
	y *= value;
	return *this;
}

Vec2& Vec2::operator /= (float value)
{
	x /= value;
	y /= value;
	return *this;
}
} // namespace Core