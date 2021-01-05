#include "Renderer.h"

namespace core {

Renderer* Renderer::s_instance = nullptr;

void Renderer::create(Window& window)
{
    s_instance = new Renderer(window.getFrameBuffer());
}

void Renderer::destroy()
{
    if (s_instance)
        delete s_instance;
}

Renderer* Renderer::getRendererInstance()
{
    if (!s_instance) 
        throw RendererNotCreatedException();
    return s_instance;
}

Renderer::Renderer(FrameBuffer& frameBuf)
    :
    m_rasterizer(frameBuf),
    m_properties{ true, false },
    m_viewport{ 0, 0, frameBuf.width(), frameBuf.height() }
{ }

Renderer::~Renderer()
{
}

void Renderer::toogleBackFaceCulling(bool enabled)
{
    m_properties.backFaceCullingFlag = enabled;
}
void Renderer::toogleWireframeRendering(bool enabled)
{
    m_properties.wireframeFlag = enabled;
}
void Renderer::setViewport(int topLeftX, int topLeftY, int width, int height)
{
    m_viewport =
    {
        topLeftX,
        topLeftY,
        width,
        height
    };
}

void Renderer::bindShader( std::shared_ptr<Shader> shader )
{
    m_shader = shader;
    m_rasterizer.bindShader(shader);
}

void Renderer::beginFrame()
{
    m_rasterizer.clearBuffers();
}

void Renderer::drawFaces(const std::vector<Face>& faces)
{
    if (!m_shader) throw NoShaderBoundException();

    for (auto& f : faces)
    {
        Triangle<VertexShaderOut> polygon(
            m_shader->vertexShader(f.v0),
            m_shader->vertexShader(f.v1),
            m_shader->vertexShader(f.v2)
        );

        if (backFaceTest(polygon))
            clip(polygon);
    }
}


void Renderer::drawIndexedTriangles(const std::vector<Vertex>& vertexBuf,
    const std::vector<unsigned short>& indexBuf)
{
    if(!m_shader) throw NoShaderBoundException();

    for( int i = 0; i < indexBuf.size(); i += 3 )
    {
        const Vertex& v0 = vertexBuf[indexBuf[i]];
        const Vertex& v1 = vertexBuf[indexBuf[i + 1]];
        const Vertex& v2 = vertexBuf[indexBuf[i + 2]];

        Triangle<VertexShaderOut> polygon(
            m_shader->vertexShader( v0 ),
            m_shader->vertexShader( v1 ),
            m_shader->vertexShader( v2 )
        );

        if (backFaceTest(polygon))
            clip(polygon);
    }
}

void Renderer::drawLines(const std::vector<LineV3>& lineBuf, const Vec4& color)
{
    for (const auto& l : lineBuf)
    {
        LineVtx line;

        line.first.pos = l.first;
        line.second.pos = l.second;

        Line<VertexShaderOut> lineVso =
        {
            m_shader->vertexShader(line.first),
            m_shader->vertexShader(line.second)
        };

        perspectiveDivide(lineVso.first);
        perspectiveDivide(lineVso.second);

        viewport(lineVso.first);
        viewport(lineVso.second);

        // Clipp line (just reject) against near plane.
        // temporary here
        if (lineVso.first.pos.z < -lineVso.first.pos.w)
        {
            return;
        }
        else if (lineVso.second.pos.z < -lineVso.second.pos.w)
        {
            return;
        }

        m_rasterizer.line(lineVso.first, lineVso.second, color);
    }
}

bool Renderer::backFaceTest(Triangle<VertexShaderOut>& polygon) const
{
    if ( !m_properties.backFaceCullingFlag )
        return true;

    const Vec3 u = polygon.v1.posView - polygon.v0.posView;
    const Vec3 v = polygon.v2.posView - polygon.v0.posView;
    Vec3 n = u.cross(v);
    n.normalize();

    Vec3 lookDir = polygon.v0.posView;
    lookDir.normalize();

    float d = lookDir.dot(n);

    return ( d <= 0 );
}

void Renderer::clip(Triangle<VertexShaderOut>& polygon)
{
    // cull tests
    if (polygon.v0.pos.x > polygon.v0.pos.w&&
        polygon.v1.pos.x > polygon.v1.pos.w&&
        polygon.v2.pos.x > polygon.v2.pos.w)
    {
        return;
    }
    if (polygon.v0.pos.x < -polygon.v0.pos.w &&
        polygon.v1.pos.x < -polygon.v1.pos.w &&
        polygon.v2.pos.x < -polygon.v2.pos.w)
    {
        return;
    }
    if (polygon.v0.pos.y > polygon.v0.pos.w&&
        polygon.v1.pos.y > polygon.v1.pos.w&&
        polygon.v2.pos.y > polygon.v2.pos.w)
    {
        return;
    }
    if (polygon.v0.pos.y < -polygon.v0.pos.w &&
        polygon.v1.pos.y < -polygon.v1.pos.w &&
        polygon.v2.pos.y < -polygon.v2.pos.w)
    {
        return;
    }
    if (polygon.v0.pos.z > polygon.v0.pos.w&&
        polygon.v1.pos.z > polygon.v1.pos.w&&
        polygon.v2.pos.z > polygon.v2.pos.w)
    {
        return;
    }
    if (polygon.v0.pos.z < -polygon.v0.pos.w &&
        polygon.v1.pos.z < -polygon.v1.pos.w &&
        polygon.v2.pos.z < -polygon.v2.pos.w )
    {
        return;
    }

    const auto Clip1 = [this](VertexShaderOut& v0, VertexShaderOut& v1, VertexShaderOut& v2)
    {
        const float alphaA = (-v0.pos.z) / (v1.pos.z - v0.pos.z);
        const float alphaB = (-v0.pos.z) / (v2.pos.z - v0.pos.z);

        const auto v0a = Math::linearInterpolation(v0, v1, alphaA);
        const auto v0b = Math::linearInterpolation(v0, v2, alphaB);

        Triangle<VertexShaderOut> clippedTri1( v0a, v1, v2 );
        Triangle<VertexShaderOut> clippedTri2( v0b, v0a, v2 );

        renderClippedPolygon(clippedTri1);
        renderClippedPolygon(clippedTri2);
    };

    const auto Clip2 = [this](VertexShaderOut& v0, VertexShaderOut& v1, VertexShaderOut& v2)
    {
        const float alpha0 = (-v0.pos.z) / (v2.pos.z - v0.pos.z);
        const float alpha1 = (-v1.pos.z) / (v2.pos.z - v1.pos.z);

        v0 = Math::linearInterpolation(v0, v2, alpha0);
        v1 = Math::linearInterpolation(v1, v2, alpha1);

        Triangle<VertexShaderOut> clippedTri( v0, v1, v2 );

        renderClippedPolygon(clippedTri);
    };

    // near clipping
    if (polygon.v0.pos.z < -polygon.v0.pos.w)
    {
        if (polygon.v1.pos.z < -polygon.v1.pos.w)
        {
            Clip2(polygon.v0, polygon.v1, polygon.v2);
        }
        else if (polygon.v2.pos.z < -polygon.v2.pos.w)
        {
            Clip2(polygon.v0, polygon.v2, polygon.v1);
        }
        else
        {
            Clip1(polygon.v0, polygon.v1, polygon.v2);
        }
    }
    else if (polygon.v1.pos.z < -polygon.v1.pos.w)
    {
        if (polygon.v2.pos.z < -polygon.v2.pos.w)
        {
            Clip2(polygon.v1, polygon.v2, polygon.v0);
        }
        else
        {
            Clip1(polygon.v1, polygon.v0, polygon.v2);
        }
    }
    else if (polygon.v2.pos.z < -polygon.v2.pos.w)
    {
        Clip1(polygon.v2, polygon.v0, polygon.v1);
    }
    else // no near clipping necessary
    {
        renderClippedPolygon(polygon);
    }
}

void Renderer::renderClippedPolygon( Triangle<VertexShaderOut>& polygon ) 
{
    perspectiveDivide(polygon.v0);
    perspectiveDivide(polygon.v1);
    perspectiveDivide(polygon.v2);

    viewport(polygon.v0);
    viewport(polygon.v1);
    viewport(polygon.v2);

    if (m_properties.wireframeFlag)
    {
        m_rasterizer.triangleWireframe(polygon.v0.pos, polygon.v1.pos, polygon.v2.pos,
                                       Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }
    else
        m_rasterizer.triangle( polygon );
}

void Renderer::perspectiveDivide( VertexShaderOut& vso ) const
{
    const float wInv = 1 / vso.pos.w;

    vso.pos.x *= wInv;
    vso.pos.y *= wInv;
    vso.pos.z *= wInv;
    vso.pos.w  = wInv;

    vso.uv *= wInv;		// for perspective correction.
    vso.color *= wInv;
    vso.intensity *= wInv;
}

void Renderer::viewport( VertexShaderOut& vso ) const
{
    vso.pos.x = ( vso.pos.x + 1 ) * m_viewport.width * 0.5f + m_viewport.topLeftX;
    vso.pos.y = ( 1 - vso.pos.y ) * m_viewport.height * 0.5f + m_viewport.topLeftY;
}

} // namespace core
