#pragma once
#include "../Math/Vec4.h"

namespace Core {

class Color
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

public:
	Color();
	Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );
	Color( const Vec4& color );
	Color( const Vec3& color );

	Vec4 toVec4() const;
	Vec3 toVec3() const;
};

} // namespace Core