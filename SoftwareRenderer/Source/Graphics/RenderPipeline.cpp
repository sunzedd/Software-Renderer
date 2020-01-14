#include "RenderPipeline.h"

namespace Core
{
	RenderPipeline::RenderPipeline( FrameBuffer& frameBuf )
		:
		m_rasterizer(frameBuf),
		m_properties{ true },
		m_viewport{ 0, 0, frameBuf.width(), frameBuf.height() }
	{ }

	void RenderPipeline::backFaceCulling( bool enabled )
	{
		m_properties.backfaceCullingFlag = enabled;
	}
	void RenderPipeline::wireframeRendering( bool enabled )
	{
		m_properties.wireframeFlag = enabled;
	}

	void RenderPipeline::bindShaderProgram( std::shared_ptr<IShaderProgram> shader )
	{
		m_shader = shader;
		m_rasterizer.bindShaderProgram(shader);
	}

	// Renderer entry point
	void RenderPipeline::run( const std::vector<Vertex>& vertexBuf, const std::vector<unsigned short>& indexBuf )
	{
		if( !m_shader )
			throw Exception( "No shader binded" );

		for( int i = 0; i < indexBuf.size(); i += 3 )
		{
			const Vertex& v0 = vertexBuf[indexBuf[i]];
			const Vertex& v1 = vertexBuf[indexBuf[i + 1]];
			const Vertex& v2 = vertexBuf[indexBuf[i + 2]];

			Triangle<VSO> polygon
			(
				m_shader->vertexShader( v0 ),
				m_shader->vertexShader( v1 ),
				m_shader->vertexShader( v2 )
			);

			if ( backFaceTest( polygon ) )
			{
				clip( polygon );
			}
		}
	}

	bool RenderPipeline::backFaceTest( Triangle<VSO>& polygon ) const
	{
		throw std::exception( "Not implemented yet!" );
	}

	void RenderPipeline::clip( Triangle<VSO>& polygon ) const
	{
		throw std::exception( "Not implemented yet!" );
	}

	void RenderPipeline::perspectiveDivide( Triangle<VSO>& polygon ) const
	{
		throw std::exception( "Not implemented yet!" );
	}

	void RenderPipeline::viewport( VSO& vso ) const
	{
		vso.pos.x = m_viewport.width * 0.5f + m_viewport.topLeftX;
		vso.pos.y = ( 1 - m_viewport.height ) * m_viewport.topLeftY;

		throw std::exception( "Not implemented yet!" );
	}

	void RenderPipeline::callRasterizer( Triangle<VSO>& polygon )
	{
		viewport(polygon.v0);
		viewport(polygon.v1);
		viewport(polygon.v2);

		if( m_properties.wireframeFlag )
			m_rasterizer.triangleWireframe();
		else
			m_rasterizer.triangle();

		throw std::exception( "Not implemented yet!" );
	}
}