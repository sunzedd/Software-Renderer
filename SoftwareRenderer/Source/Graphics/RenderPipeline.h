#pragma once
#include <vector>
#include <string>
#include "IShaderProgram.h"
#include "FrameBuffer.h"
#include "Rasterizer.h"

namespace Core
{
	class RenderPipeline final
	{
	public:
		class Exception : public std::exception
		{
		public:
			Exception(const std::string& msg)
				:
				exception(msg.c_str()) { }
		};

	public:
		RenderPipeline( FrameBuffer& frameBuf );

		void backFaceCulling( bool enabled );
		void bindShaderProgram( std::shared_ptr<IShaderProgram> shader );

		// Renderer entry point
		void run( const std::vector<Vertex>& vertexBuf,  const std::vector<unsigned short>& indexBuf );
	private:
		

	private:
		Rasterizer m_rasterizer;
		std::shared_ptr<IShaderProgram> m_shader;

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