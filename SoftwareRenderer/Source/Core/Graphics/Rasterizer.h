#pragma once
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "Vertex.h"
#include "IShaderProgram.h"

namespace Core
{
	class Rasterizer
	{
	public:
		Rasterizer( FrameBuffer& frameBuf );

		void bindShaderProgram( std::shared_ptr<IShaderProgram> shader );

		void line( const Vec2& p0, const Vec2& p1, const Vec4& color );
		void line( const Vertex& v0, const Vertex& v1 );

		void triangleWireframe();
		void triangle();
	protected:
		FrameBuffer& m_frameBuf;
		DepthBuffer m_depthBuf;
		std::shared_ptr<IShaderProgram> m_shader;
	};
}