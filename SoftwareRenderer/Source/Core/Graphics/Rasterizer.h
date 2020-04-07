#pragma once
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "Vertex.h"
#include "Shader.h"
#include "Triangle.h"

namespace core {

class Rasterizer
{
public:
    Rasterizer( FrameBuffer& frameBuf );

    void clearBuffers();

    void bindShader(std::shared_ptr<Shader> shader);

    void line(const Vec2& p0, const Vec2& p1, const Color& color);
    void line(const Vec3& p0, const Vec3& p1, const Color& color);
    void line(VertexShaderOut& v0, VertexShaderOut& v1, const Color& color);

    void triangleWireframe(const Vec3& p0, const Vec3& p1, const Vec3& p2,
                           const Color& color);

    void triangle(const Triangle<VertexShaderOut>& triangle);
protected:
    void triangleFlatTop(const VertexShaderOut& v0, const VertexShaderOut& v1, const VertexShaderOut& v2);
    void triangleFlatBottom(const VertexShaderOut& v0, const VertexShaderOut& v1, const VertexShaderOut& v2);
    void triangleFlat(const VertexShaderOut& it0, const VertexShaderOut& it1, const VertexShaderOut& it2,
                      const VertexShaderOut& dv0, const VertexShaderOut& dv1, VertexShaderOut itEdge1);

protected:
    FrameBuffer& m_frameBuf;
    DepthBuffer m_depthBuf;
    std::shared_ptr<Shader> m_shader;
};

} // namespace core
