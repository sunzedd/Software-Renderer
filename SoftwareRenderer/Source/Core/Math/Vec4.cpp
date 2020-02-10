#include "Vec4.h"

namespace Core {

	Vec4::Vec4() 
		:
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(1.0f)
	{ }

	Vec4::Vec4(float x, float y, float z, float w)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{ }

	Vec4::Vec4(const Vec3& vec3)
		:
		x(vec3.x),
		y(vec3.y),
		z(vec3.z),
		w(1.0f)
	{ }

	Vec4::Vec4(const Vec3& vec3, float w)
		:
		x(vec3.x),
		y(vec3.y),
		z(vec3.z),
		w(w)
	{ }

	Vec4& Vec4::operator = (const Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 1.0f;

		return *this;
	}


	Vec4 operator + (const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	Vec4 operator - (const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	Vec4 operator - (const Vec4& vec)
	{
		return vec * -1;
	}

	Vec4 operator * (const Vec4& vec, float value)
	{
		return Vec4(vec.x * value, vec.y * value, vec.z * value, vec.w * value);
	}

	Vec4 operator / (const Vec4& vec, float value)
	{
		return Vec4(vec.x / value, vec.y / value, vec.z / value, vec.w / value);
	}

	Vec4& Vec4::operator += (const Vec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	Vec4& Vec4::operator -= (const Vec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	Vec4& Vec4::operator *= (float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	Vec4& Vec4::operator /= (float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	Vec4& Vec4::operator *= (const Mat4& mat4)
	{
		float x_ = x * mat4.m[0][0] + y * mat4.m[1][0] + z * mat4.m[2][0] + w * mat4.m[3][0];
		float y_ = x * mat4.m[0][1] + y * mat4.m[1][1] + z * mat4.m[2][1] + w * mat4.m[3][1];
		float z_ = x * mat4.m[0][2] + y * mat4.m[1][2] + z * mat4.m[2][2] + w * mat4.m[3][2];
		float w_ = x * mat4.m[0][3] + y * mat4.m[1][3] + z * mat4.m[2][3] + w * mat4.m[3][3];

		x = x_;
		y = y_;
		z = z_;
		w = w_;

		return *this;
	}

	Vec4 operator * (const Vec4& vec4, const Mat4& mat4)
	{
		Vec4 v;
		v.x = vec4.x * mat4.m[0][0] + vec4.y * mat4.m[1][0] + vec4.z * mat4.m[2][0] + vec4.w * mat4.m[3][0];
		v.y = vec4.x * mat4.m[0][1] + vec4.y * mat4.m[1][1] + vec4.z * mat4.m[2][1] + vec4.w * mat4.m[3][1];
		v.z = vec4.x * mat4.m[0][2] + vec4.y * mat4.m[1][2] + vec4.z * mat4.m[2][2] + vec4.w * mat4.m[3][2];
		v.w = vec4.x * mat4.m[0][3] + vec4.y * mat4.m[1][3] + vec4.z * mat4.m[2][3] + vec4.w * mat4.m[3][3];
		
		return v;
	}

	float Vec4::length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	Vec4 Vec4::getHadamard(const Vec4& rhs) const
	{
		Vec4 out(*this);

		out.x *= rhs.x;
		out.y *= rhs.y;
		out.z *= rhs.z;
		out.w *= rhs.w;

		return out;
	}

	Vec4 Vec4::getNormalized() const
	{
		Vec4 out(*this);

		const float l = out.length();
		out /= l;

		return out;
	}

	Vec4& Vec4::saturate()
	{
		x = std::min(1.0f, std::max(0.0f, x));
		y = std::min(1.0f, std::max(0.0f, y));
		z = std::min(1.0f, std::max(0.0f, z));
		w = std::min(1.0f, std::max(0.0f, w));
	
		return *this;
	}
}