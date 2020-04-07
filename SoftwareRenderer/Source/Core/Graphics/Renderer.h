#pragma once
#include <vector>
#include <string>

#include "../Exceptions.h"
#include "../Window.h"

#include "Shader.h"
#include "FrameBuffer.h"
#include "Rasterizer.h"
#include "Triangle.h"
#include "Common.h"

namespace core {

class Renderer final
{
    static Renderer* s_instance;

    struct _Properties
    {
        bool backFaceCullingFlag;
        bool wireframeFlag;
    };

    struct _Viewport
    {
        int topLeftX;
        int topLeftY;
        int width;
        int height;
    };

public:
    static void create(Window& window);
    static void destroy();
    static Renderer* getRendererInstance();

    void toogleBackFaceCulling(bool enable);
    void toogleWireframeRendering(bool enable);
    void setViewport(int topLeftX, int topLeftY, int width, int height);

    void bindShader(std::shared_ptr<Shader> shader);

    // Renderer entry point
    void beginFrame();
    
    void drawFaces(const std::vector<Face>& faces);
    void drawIndexedTriangles(const std::vector<Vertex>& vertexBuf,
                              const std::vector<unsigned short>& indexBuf);
    void drawLines(const std::vector<LineV3>& lineBuf, const Vec4& color);

private:
    Renderer(FrameBuffer& frameBuf);
    ~Renderer();

    bool backFaceTest(Triangle<VertexShaderOut>& polygon) const;
    void clip(Triangle<VertexShaderOut>& polygon);
    void renderClippedPolygon(Triangle<VertexShaderOut>& polygon);
    void perspectiveDivide(VertexShaderOut& vso) const;
    void viewport(VertexShaderOut& vso) const;

private:
    Rasterizer m_rasterizer;
    std::shared_ptr<Shader> m_shader;

    _Properties m_properties;
    _Viewport m_viewport;
};

} // namespace core
