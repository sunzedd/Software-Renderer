#pragma once
#include <algorithm>
#include <SFML/Graphics/Color.hpp>

#include "Vec2.h"

namespace core {
	class Vec4;
}

namespace core {

class  Vec3
{
public:
	float x, y, z;

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec2& vec2);
	Vec3(const Vec4& vec4);
	explicit Vec3(sf::Color color);

	Vec3& operator = (const Vec4& rhs);

	Vec3 friend operator + (const Vec3& vec, float value);
	Vec3 friend operator + (const Vec3& lhs, const Vec3& rhs);
	Vec3 friend operator - (const Vec3& lhs, const Vec3& rhs);
	Vec3 friend operator - (const Vec3& vec);
	Vec3 friend operator * (const Vec3& vec, float value);
	Vec3 friend operator / (const Vec3& vec, float value);

	Vec3& operator += (const Vec3& rhs);
	Vec3& operator -= (const Vec3& rhs);
	Vec3& operator *= (float value);
	Vec3& operator /= (float value);

	Vec3& rotate(const Vec3& axis, float angle);

	float length() const;
	float dot(const Vec3& other) const;
	Vec3 normalized() const;
	Vec3& normalize();
	Vec3 cross(const Vec3& other) const;
	float distance(const Vec3& other) const;

	Vec3& hadamard(const Vec3& rhs);
	Vec3 getHadamard(const Vec3& rhs) const;

	Vec3& saturate();
	Vec3& getSaturated() const;

	static Vec3 forward();
	static Vec3 right();
	static Vec3 up();
};

} // namespace core
