#include "Mat4.h"
#include "Vec3.h"

#include <iostream>

namespace Core {

Mat4::Mat4()
{
	std::memset(data, 0.0f, sizeof(float) * 16);
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
}

Mat4::Mat4(const float data[16])
{
	std::memcpy(this->data, data, sizeof(data));
}

Mat4::Mat4(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Mat4& Mat4::operator *= (const Mat4& rhs)
{
	Mat4 tmp(*this);

	for (int32_t row = 0; row < 4; row++)
	{
		for (int32_t col = 0; col < 4; col++)
		{
			float sum = 0.0f;
			for (int32_t e = 0; e < 4; e++)
			{
				sum += m[row][e] * rhs.m[e][col];
			}
			tmp.m[row][col] = sum;
		}
	}

	*this = tmp;

	return *this;
}

Mat4 operator * (const Mat4& lhs, const Mat4& rhs)
{
	Mat4 result;

	for (int32_t row = 0; row < 4; row++)
	{
		for (int32_t col = 0; col < 4; col++)
		{
			float sum = 0.0f;
			for (int32_t e = 0; e < 4; e++)
			{
				sum += lhs.m[row][e] * rhs.m[e][col];
			}
			result.m[row][col] = sum;
		}
	}

	return result;
}

Mat4 operator !(const Mat4& mat)
{
	Mat4 trasposed;

	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			trasposed.m[j][k] = mat.m[k][j];
		}
	}

	return trasposed;
}


Mat4 Mat4::translation(const Vec3& t)
{
	return {
		1,   0,   0,   0,
		0,   1,   0,   0,
		0,   0,   1,   0,
		t.x, t.y, t.z, 1
	};
}

Mat4 Mat4::scale(const Vec3& t)
{
	return {
		t.x, 0,   0,	0,
		0,	 t.y, 0,	0,
		0,	 0,   t.z,  0,
		0,	 0,   0,	1
	};
}

Mat4 Mat4::rotationX(float angle)
{
	float rad = MathFunc::toRadians(angle);

	const float cosX = cos(rad);
	const float sinX = sin(rad);

	return {
		1.0f,  0.0f,  0.0f, 0.0f,
		0.0f,  cosX, -sinX, 0.0f,
		0.0f,  sinX,  cosX, 0.0f,
		0.0f,  0.0f,  0.0f, 1.0f
	};
}

Mat4 Mat4::rotationY(float angle)
{
	float rad = MathFunc::toRadians(angle);

	const float cosY = cos(rad);
	const float sinY = sin(rad);

	return {
		 cosY, 0.0f,  sinY, 0.0f,
		 0.0f, 1.0f,  0.0f, 0.0f,
		-sinY, 0.0f,  cosY, 0.0f,
		 0.0f, 0.0f,  0.0f, 1.0f
	};
}

Mat4 Mat4::rotationZ(float angle)
{
	float rad = MathFunc::toRadians(angle);

	const float cosZ = cos(rad);
	const float sinZ = sin(rad);

	return {
		 cosZ, -sinZ, 0.0f, 0.0f,
		 sinZ,  cosZ, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 1.0f
	};
}

Mat4 Mat4::rotationXYZ(const Vec3& angle)
{
	Mat4 x = Mat4::rotationX(angle.x);
	Mat4 y = Mat4::rotationY(angle.y);
	Mat4 z = Mat4::rotationZ(angle.z);

	return x * y * z;
}

#ifdef EXPERIMENTAL
Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	const Vec3 f = (center - eye).normalize();
	const Vec3 s = f.cross(up).normalize();
	const Vec3 u = s.cross(f);

	Mat4 result;
	result.m[0][0] = s.x;
	result.m[1][0] = s.y;
	result.m[2][0] = s.z;
	result.m[0][1] = u.x;
	result.m[1][1] = u.y;
	result.m[2][1] = u.z;
	result.m[0][2] = -f.x;
	result.m[1][2] = -f.y;
	result.m[2][2] = -f.z;
	result.m[3][0] = -s.dot(eye);
	result.m[3][1] = -u.dot(eye);
	result.m[3][2] = f.dot(eye);

	return result;
}

#else
Mat4 Mat4::lookAt(const Vec3& pos, const Vec3& object, const Vec3& up)
{
	Mat4 result;

	Vec3 f = (object - pos).normalized();
	Vec3 s = f.cross(-up.normalized());
	Vec3 u = s.cross(f);

	result.m[0][0] = s.x;
	result.m[1][0] = s.y;
	result.m[2][0] = s.z;

	result.m[0][1] = u.x;
	result.m[1][1] = u.y;
	result.m[2][1] = u.z;

	result.m[0][2] = -f.x;
	result.m[1][2] = -f.y;
	result.m[2][2] = -f.z;

	return result * translation(Vec3(-pos.x, -pos.y, -pos.z));
}
#endif

Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4 result;

	result.m[0][0] = 2.0f / (right - left);

	result.m[1][1] = 2.0f / (top - bottom);

	result.m[2][2] = 2.0f / (near - far);

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (bottom + top) / (bottom - top);
	result.m[3][2] = (far + near) / (far - near);

	return result;
}

Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	const float fovRad = MathFunc::toRadians(fov);
	const float tanHalfFovy = ( tan(fovRad) / 2.0f );
	Mat4 result;

	result.m[0][0] = 1 / (aspectRatio * tanHalfFovy);
	result.m[1][1] = 1 / tanHalfFovy;
	result.m[2][2] = -(far + near) / (far - near);
	result.m[2][3] = -1;
	result.m[3][2] = -2 * (far * near) / (far - near);
	result.m[3][3] = 0;

	return result;
}

} // namespace Core
