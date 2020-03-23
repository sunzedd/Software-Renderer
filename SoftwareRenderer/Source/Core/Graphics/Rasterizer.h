#pragma once
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "Vertex.h"
#include "ShaderProgram.h"
#include "Triangle.h"

namespace core {

class Rasterizer
{
public:
	Rasterizer( FrameBuffer& frameBuf );

	void clearBuffers();

	void bindShaderProgram( std::shared_ptr<ShaderProgram> shader );

	void line( const Vec2& p0, const Vec2& p1, const Vec4& color );
	void line( const Vec3& p0, const Vec3& p1, const Vec4& color );
	void line( VSO& v0, VSO& v1, const Vec4& color );

	void triangleWireframe( const Vec3& p0, const Vec3& p1, const Vec3& p2,
		const Vec4& color );

	void triangle(const Triangle<VSO>& triangle);
protected:
	void triangleFlatTop(const VSO& v0, const VSO& v1, const VSO& v2);
	void triangleFlatBottom(const VSO& v0, const VSO& v1, const VSO& v2);
	void triangleFlat(const VSO& it0, const VSO& it1, const VSO& it2,
		const VSO& dv0, const VSO& dv1, VSO itEdge1);

protected:
	FrameBuffer& m_frameBuf;
	DepthBuffer m_depthBuf;
	std::shared_ptr<ShaderProgram> m_shader;
};

} // namespace core
