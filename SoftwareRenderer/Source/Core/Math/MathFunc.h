#pragma once
#include "Vec3.h"
#include "Vec4.h"

#define CORE_PI 3.14159265359

namespace Core {
class MathFunc
{
public:
	template<typename T>
	static T linearInterpolation(const T& src, const T& dst, float linterpFactor)
	{
		return src + (dst - src) * linterpFactor;
	}
	static inline float toRadians(float degrees)
	{
		return (float)(degrees * (CORE_PI / 180.0f));
	}
	static inline float toDegrees(float rad)
	{
		return (float)(rad / (CORE_PI / 180.0f));
	}

	static Vec3 lineIntersectPlane(const Vec3& planePoint, const Vec3& planeNorm, const Vec3& lineStart, const Vec3& lineEnd);
	static Vec4 computePlaneEquation(const Vec3& p1, const Vec3& p2, const Vec3& p3);

private:
	MathFunc() {} 
};
} // namespace Core