#pragma once
#include "Math.h"
#include <cmath>

#define EXPERIMENTAL

namespace core {
	class Vec3;
}

namespace core {

/*
	Row major matrix order.

	Multiplication with vectors order:

	[x, y, z, w] * [1, 0, 0, 0] = [x', y', z', w']
				   [0, 1, 0, 0]
				   [0, 0, 1, 0]
				   [0, 0, 0, 1]
*/

class Mat4
{
public:
	union
	{
		float m[4][4];
		float data[16];
	};

	Mat4();
	Mat4(const float data[16]);
	Mat4(float m00, float m01, float m02, float m03,
		  float m10, float m11, float m12, float m13, 
		  float m20, float m21, float m22, float m23, 
		  float m30, float m31, float m32, float m33);

public:

	Mat4& operator *= (const Mat4& rhs);
	Mat4 friend operator * (const Mat4& lhs, const Mat4& rhs);

	Mat4 friend operator !(const Mat4& mat); 		// Does transpose

	static Mat4 translation(const Vec3& t);
	static Mat4 scale(const Vec3& s);

	static Mat4 rotationX(float angle);
	static Mat4 rotationY(float angle);
	static Mat4 rotationZ(float angle);
	static Mat4 rotationXYZ(const Vec3& angle);

#ifdef EXPERIMENTAL
	// Right handed coordinate system
	static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
#else
	static Mat4 lookAt(const Vec3& pos, const Vec3& object, const Vec3& up);
#endif
	static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static Mat4 perspective(float fov, float aspectRatio, float near, float far);
};

} // namespace core
