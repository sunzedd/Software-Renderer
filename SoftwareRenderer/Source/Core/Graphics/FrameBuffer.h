#pragma once
#include "Buffer.h"
#include "Color.h"

namespace Core {

class FrameBuffer : public Buffer<Color>
{
public:
	FrameBuffer( int width, int height )
		:
		Buffer( width, height )
	{ }

	void setPixel( int x, int y, const Vec4& color )
	{
		Buffer::set( x, y, Color( color ) );
	}
	
	void setPixel(int x, int y, const Vec3& color)
	{
		Buffer::set( x, y, Color( color ) );
	}

	const Color* pixels() const
	{
		return m_pData.get();
	}
};

} // namespace Core