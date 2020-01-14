#pragma once
#include <vector>
#include "IShaderProgram.h"
#include "FrameBuffer.h"
#include "Rasterizer.h"

namespace Core
{
	class RenderPipeline final
	{
	public:
		RenderPipeline( FrameBuffer& frameBuf );

		void backFaceCulling( bool enabled );

		// Renderer entry point
		void run( const std::vector<Vertex>& vertexBuf,  const std::vector<unsigned short>& indexBuf );
	private:

	private:
		Rasterizer m_rasterizer;

		struct 
		{
			bool backfaceCullingFlag;
		}
		m_properties;

		struct
		{
			int topLeftX;
			int topLeftY;
			int width;
			int height;
		}
		m_viewport;
	};
}