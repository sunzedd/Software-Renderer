#include "Math.h"

namespace Core {

Vec3 Math::lineIntersectPlane(const Vec3& planePoint, const Vec3& planeNorm, const Vec3& lineStart, const Vec3& lineEnd)
{
	Vec3 n = planeNorm.normalized();
	float d = -n.dot(planePoint);
	float ad = lineStart.dot(n);
	float bd = lineEnd.dot(n);
	float t = (-d - ad) / (bd - ad);

	Vec3 line = lineEnd - lineStart;
	Vec3 intersec = line * t;

	return lineStart + intersec;
}

Vec4 Math::computePlaneEquation(const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
	float a1 = p2.x - p1.x;
	float b1 = p2.y - p1.y;
	float c1 = p2.z - p1.z;
	float a2 = p3.x - p1.x;
	float b2 = p3.y - p1.y;
	float c2 = p3.z - p1.z;
	float a = b1 * c2 - b2 * c1;
	float b = a2 * c1 - a1 * c2;
	float c = a1 * b2 - b1 * a2;
	float d = (-a * p1.x - b * p1.y - c * p1.z);

	return Vec4( a, b, c, d );
}

} // namespace Core
