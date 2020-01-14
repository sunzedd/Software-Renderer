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
		float x, y, z, w;

		Vec4();
		Vec4(float x, float y, float z, float w);
		Vec4(const Vec3& vec3);

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
	};
}