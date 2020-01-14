#pragma once
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"

namespace Core
{
	class Vertex
	{
	public:
		Vec3 pos;
		Vec4 n;
		Vec2 uv;
		Vec4 color;

	public:
		Vertex();
		Vertex( const Vec3& pos, const Vec3& n, const Vec2& uv, const Vec4& color );

		Vertex& operator += ( const Vertex& rhs );
		Vertex& operator -= ( const Vertex& rhs );
		Vertex& operator *= ( float val );
		Vertex& operator /= ( float val );

		friend Vertex operator + ( const Vertex& lhs, const Vertex& rhs );
		friend Vertex operator - ( const Vertex& lhs, const Vertex& rhs );
		friend Vertex operator * ( const Vertex& v, float val );
		friend Vertex operator / ( const Vertex& v, float val );
	};
}