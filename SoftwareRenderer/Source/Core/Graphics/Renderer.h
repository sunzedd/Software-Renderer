#pragma once
#include <vector>
#include <string>

#include "../Exceptions.h"
#include "../Window.h"

#include "ShaderProgram.h"
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

    void bindShaderProgram(std::shared_ptr<ShaderProgram> shader);

    // Renderer entry point
    void beginFrame();
    
    void drawFaces(const std::vector<Face>& faces);
    void drawIndexedTriangles(const std::vector<Vertex>& vertexBuf,
                              const std::vector<unsigned short>& indexBuf);
    void drawLines(const std::vector<LineV3>& lineBuf, const Vec4& color);

private:
    Renderer(FrameBuffer& frameBuf);
    ~Renderer();

    bool backFaceTest(Triangle<VSO>& polygon) const;
    void clip(Triangle<VSO>& polygon);
    void renderClippedPolygon(Triangle<VSO>& polygon);
    void perspectiveDivide(VSO& vso) const;
    void viewport(VSO& vso) const;

private:
    Rasterizer m_rasterizer;
    std::shared_ptr<ShaderProgram> m_shader;

    _Properties m_properties;
    _Viewport m_viewport;
};

} // namespace core
