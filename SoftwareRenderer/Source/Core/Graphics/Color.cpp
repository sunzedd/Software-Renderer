#include "Color.h"

namespace core {

Color::Color()
	:
	r(255), g(255), b(255), a(255)
{ }

Color::Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a /* = 255 */ )
	:
	r(r), g(g), b(b), a(a) 
{ }

Color::Color( const Vec4& color ) 
{
	r = static_cast<unsigned char>( color.x * 255 );
	g = static_cast<unsigned char>( color.y * 255 );
	b = static_cast<unsigned char>( color.z * 255 );
	a = static_cast<unsigned char>( color.w * 255 );
}

Color::Color( const Vec3& color )
{
	r = static_cast<unsigned char>( color.x * 255 );
	g = static_cast<unsigned char>( color.y * 255 );
	b = static_cast<unsigned char>( color.z * 255 );
	a = 255;
}

Vec4 Color::toVec4() const
{
	return
	{
		static_cast<float>(r) / 255.0f,
		static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f,
		static_cast<float>(a) / 255.0f
	};
}

Vec3 Color::toVec3() const 
{
	return
	{
		static_cast<float>(r) / 255.0f,
		static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f
	};
}

} // namespace core
