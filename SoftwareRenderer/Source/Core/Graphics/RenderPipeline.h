#pragma once
#include <vector>
#include <string>
#include "IShaderProgram.h"
#include "FrameBuffer.h"
#include "Rasterizer.h"
#include "Triangle.h"
#include "Common.h"

namespace Core {

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
	void wireframeRendering( bool enabled );
	void setViewport(int topLeftX, int topLeftY, int width, int height);
	void bindShaderProgram( std::shared_ptr<IShaderProgram> shader );

	// Renderer entry point
	void beginFrame();
	void runTriangles( const std::vector<Vertex>& vertexBuf,  const std::vector<unsigned short>& indexBuf );
	void runLines(const std::vector<LineV3>& lineBuf, const Vec4& color);
private:
	bool backFaceTest( Triangle<VSO>& polygon ) const;
	void clip( Triangle<VSO>& polygon );
	void renderClippedPolygon( Triangle<VSO>& polygon );
	void perspectiveDivide( VSO& vso ) const;
	void viewport( VSO& vso ) const;

private:
	Rasterizer m_rasterizer;
	std::shared_ptr<IShaderProgram> m_shader;

	struct 
	{
		bool backFaceCullingFlag;
		bool wireframeFlag;
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

} // namespace Core