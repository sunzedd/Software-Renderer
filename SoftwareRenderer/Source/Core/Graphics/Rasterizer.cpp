#include "Rasterizer.h"

namespace Core
{
	Rasterizer::Rasterizer( FrameBuffer& frameBuf )
		:
		m_frameBuf( frameBuf ),
		m_depthBuf( frameBuf.width(), frameBuf.height() )
	{ }

	void Rasterizer::bindShaderProgram( std::shared_ptr<IShaderProgram> shader )
	{
		m_shader = shader;
	}

	void Rasterizer::line( const Vec2& p0, const Vec2& p1, const Vec4& color )
	{
		throw std::exception("Not implemented yet");
	}

	void Rasterizer::line( const Vertex& v0, const Vertex& v1 )
	{
		throw std::exception("Not implemented yet");
	}

	void Rasterizer::triangleWireframe()
	{
		throw std::exception("Not implemented yet");
	}

	void Rasterizer::triangle()
	{
		throw std::exception("Not implemented yet");
	}
}