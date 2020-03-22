#pragma once
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"

namespace core {

class Vertex
{
public:
	Vec3 pos;
	Vec4 n;
	Vec2 uv;
	Vec4 color;

public:
	Vertex& operator += ( const Vertex& rhs );
	Vertex& operator -= ( const Vertex& rhs );
	Vertex& operator *= ( float val );
	Vertex& operator /= ( float val );

	friend Vertex operator + ( const Vertex& lhs, const Vertex& rhs );
	friend Vertex operator - ( const Vertex& lhs, const Vertex& rhs );
	friend Vertex operator * ( const Vertex& v, float val );
	friend Vertex operator / ( const Vertex& v, float val );
};

} // namespace core
