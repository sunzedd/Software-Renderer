#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Core {
class Mat4;
}

namespace Core {
class  Vec4
{
public:
	union
	{
		struct { float x, y, z, w; };
		float data[4];
	};

	Vec4();
	Vec4(float x, float y, float z, float w);
	Vec4(const Vec3& vec3);
	Vec4(const Vec3& vec3, float w);

	Vec4& operator = (const Vec3& rhs);

	Vec4 friend operator + (const Vec4& lhs, const Vec4& rhs);
	Vec4 friend operator - (const Vec4& lhs, const Vec4& rhs);
	Vec4 friend operator - (const Vec4& vec);
	Vec4 friend operator * (const Vec4& vec, float value);
	Vec4 friend operator / (const Vec4& vec, float value);

	Vec4& operator += (const Vec4& rhs);
	Vec4& operator -= (const Vec4& rhs);
	Vec4& operator *= (float value);
	Vec4& operator /= (float value);

	// with matrices
	Vec4& operator *= (const Mat4& mat4);
	Vec4 friend operator * (const Vec4& vec4, const Mat4& mat4);

	float length() const;

	float dot(const Vec4& rhs) const;

	Vec4 getHadamard(const Vec4& rhs) const;
	Vec4 getNormalized() const;
	Vec4& saturate();
};
} // namespace Core