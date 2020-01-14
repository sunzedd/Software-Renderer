#include "RenderPipeline.h"

namespace Core
{
	RenderPipeline::RenderPipeline(FrameBuffer& frameBuf)
		:
		m_rasterizer(frameBuf),
		m_properties{ true },
		m_viewport{ 0, 0, frameBuf.width(), frameBuf.height() }
	{ }

	void RenderPipeline::backFaceCulling(bool enabled)
	{
		m_properties.backfaceCullingFlag = enabled;
	}

	void RenderPipeline::bindShaderProgram( std::shared_ptr<IShaderProgram> shader )
	{
		m_shader = shader;
		m_rasterizer.bindShaderProgram( shader );
	}

	// Renderer entry point
	void RenderPipeline::run( const std::vector<Vertex>& vertexBuf, const std::vector<unsigned short>& indexBuf )
	{
		if (!m_shader)
			throw Exception("No shader binded");
	}
}