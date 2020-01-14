#pragma once
#include "Vec2.h"

namespace Core {

	class Vec2i
	{
	public:
		int x, y;

		Vec2i();
		Vec2i(int x, int y);

		Vec2i friend operator + (const Vec2i& lhs, const Vec2i& rhs);
		Vec2i friend operator - (const Vec2i& lhs, const Vec2i& rhs);
		Vec2i friend operator - (const Vec2i& vec);
		Vec2i friend operator * (const Vec2i& vec, int value);
		Vec2 friend operator / (const Vec2i& vec, float value);

		Vec2i& operator += (const Vec2i& rhs);
		Vec2i& operator -= (const Vec2i& rhs);
		Vec2i& operator *= (int value);
	};

}
