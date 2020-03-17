#include "Vec3.h"
#include "Vec4.h"

namespace Core {
Vec3::Vec3() 
	:
	x(0.0f),
	y(0.0f),
	z(0.0f)
{ }

Vec3::Vec3(float x, float y, float z)
	:
	x(x),
	y(y),
	z(z)
{ }

Vec3::Vec3(const Vec2& vec2)
	:
	x(vec2.x),
	y(vec2.y),
	z(1.0)
{ }

Vec3::Vec3(const Vec4& vec4)
	:
	x(vec4.x),
	y(vec4.y),
	z(vec4.z)
{ }

Vec3::Vec3(sf::Color color)
	:
	x((float)color.r / 255.0f),
	y((float)color.g / 255.0f),
	z((float)color.b / 255.0f)
{ }

Vec3& Vec3::operator = (const Vec4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

Vec3 operator + (const Vec3& vec, float value)
{
	return Vec3(vec.x + value, vec.y + value, vec.z + value);
}
Vec3 operator + (const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator - (const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3 operator - (const Vec3& vec)
{
	return vec * -1;
}

Vec3 operator * (const Vec3& vec, float value)
{
	return Vec3(vec.x * value, vec.y * value, vec.z * value);
}

Vec3 operator / (const Vec3& vec, float value)
{
	return Vec3(vec.x / value, vec.y / value, vec.z / value);
}

Vec3& Vec3::operator += (const Vec3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3& Vec3::operator -= (const Vec3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec3& Vec3::operator *= (float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vec3& Vec3::operator /= (float value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

Vec3& Vec3::rotate(const Vec3& axis, float angle) 
{
	const float sinAngle = (float)sin(-angle);
	const float cosAngle = (float)cos(-angle);

	*this = cross(axis * sinAngle) + (*this * cosAngle) + axis * (dot(axis * (1 - cosAngle)));

	return *this;
}

float Vec3::dot(const Vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const
{
	float l = length();
	return Vec3(x / l, y / l, z / l);
}

Vec3& Vec3::normalize()
{
	float l = length();
	if (l != 0)
		*this /= l;

	return *this;
}

Vec3 Vec3::cross(const Vec3& other) const
{
	return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vec3::distance(const Vec3& other) const
{
	float a = x - other.x;
	float b = y - other.y;
	float c = z - other.z;
	return sqrt(a * a + b * b + c * c);
}

Vec3& Vec3::hadamard(const Vec3& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
};

Vec3 Vec3::getHadamard(const Vec3& rhs) const
{
	Vec3 temp(*this);
	temp.hadamard(rhs);

	return temp;
}

Vec3& Vec3::saturate()
{
	x = std::min(1.0f, std::max(0.0f, x));
	y = std::min(1.0f, std::max(0.0f, y));
	z = std::min(1.0f, std::max(0.0f, z));
	return *this;
}
Vec3& Vec3::getSaturated() const
{
	Vec3 out(*this);
	out.saturate();
	
	return out;
}
} // namespace Core