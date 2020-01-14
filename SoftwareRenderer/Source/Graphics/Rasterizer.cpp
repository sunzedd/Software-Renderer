#include "Rasterizer.h"

namespace Core
{
	Rasterizer::Rasterizer( FrameBuffer& frameBuf )
		:
		m_frameBuf( frameBuf ),
		m_depthBuf( frameBuf.width(), frameBuf.height() )
	{ }

	void Rasterizer::line( const Vec2& p0, const Vec2& p1, const Vec4& color )
	{ }

	void Rasterizer::line( const Vertex& v0, const Vertex& v1 )
	{
		throw std::exception("Not implemented yet");
	}

	void Rasterizer::triangle()
	{
		throw std::exception("Not implemented yet");
	}
}