#pragma once

namespace Core {
	class Vec2i;
}

namespace Core {
class  Vec2
{
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2i& vec2i);

	Vec2 friend operator + (const Vec2& lhs, const Vec2& rhs);
	Vec2 friend operator - (const Vec2& lhs, const Vec2& rhs);
	Vec2 friend operator - (const Vec2& vec);
	Vec2 friend operator * (const Vec2& vec, float value);
	Vec2 friend operator / (const Vec2& vec, float value);

	Vec2 friend operator - (const Vec2& vec, float val);

	Vec2& operator += (const Vec2& rhs);
	Vec2& operator -= (const Vec2& rhs);
	Vec2& operator *= (float value);
	Vec2& operator /= (float value);
};
} // namespace Core
