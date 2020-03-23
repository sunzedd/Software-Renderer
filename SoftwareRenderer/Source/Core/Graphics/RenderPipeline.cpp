#include "RenderPipeline.h"

namespace core {

RenderPipeline* RenderPipeline::s_instance = nullptr;

void RenderPipeline::create(Window& window)
{
    s_instance = new RenderPipeline(window.getFrameBuffer());
}

void RenderPipeline::destroy()
{
    if (s_instance)
        delete s_instance;
}

RenderPipeline& RenderPipeline::instance()
{
    if (!s_instance) throw RenderPipelineNotCreatedException();
    return *s_instance;
}

RenderPipeline::RenderPipeline(FrameBuffer& frameBuf)
    :
    m_rasterizer(frameBuf),
    m_properties{ true, false },
    m_viewport{ 0, 0, frameBuf.width(), frameBuf.height() }
{ }

RenderPipeline::~RenderPipeline()
{
}

void RenderPipeline::toogleBackFaceCulling(bool enabled)
{
    m_properties.backFaceCullingFlag = enabled;
}
void RenderPipeline::toogleWireframeRendering(bool enabled)
{
    m_properties.wireframeFlag = enabled;
}
void RenderPipeline::setViewport(int topLeftX, int topLeftY, int width, int height)
{
    m_viewport =
    {
        topLeftX,
        topLeftY,
        width,
        height
    };
}

void RenderPipeline::bindShaderProgram( std::shared_ptr<ShaderProgram> shader )
{
    m_shader = shader;
    m_rasterizer.bindShaderProgram(shader);
}

void RenderPipeline::beginFrame()
{
    m_rasterizer.clearBuffers();
}

// Renderer entry point
void RenderPipeline::drawIndexedTriangles(const std::vector<Vertex>& vertexBuf,
    const std::vector<unsigned short>& indexBuf)
{
    if(!m_shader) throw NoShaderBoundException();

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

        if (backFaceTest(polygon))
        {
            clip(polygon);
        }
    }
}

void RenderPipeline::drawLines(const std::vector<LineV3>& lineBuf, const Vec4& color)
{
    for (const auto& l : lineBuf)
    {
        LineVtx line;

        line.first.pos = l.first;
        line.second.pos = l.second;

        Line<VSO> lineVso =
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

bool RenderPipeline::backFaceTest(Triangle<VSO>& polygon) const
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

void RenderPipeline::clip(Triangle<VSO>& polygon)
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

    const auto Clip1 = [this](VSO& v0, VSO& v1, VSO& v2)
    {
        const float alphaA = (-v0.pos.z) / (v1.pos.z - v0.pos.z);
        const float alphaB = (-v0.pos.z) / (v2.pos.z - v0.pos.z);

        const auto v0a = Math::linearInterpolation(v0, v1, alphaA);
        const auto v0b = Math::linearInterpolation(v0, v2, alphaB);

        Triangle<VSO> clippedTri1( v0a, v1, v2 );
        Triangle<VSO> clippedTri2( v0b, v0a, v2 );

        renderClippedPolygon(clippedTri1);
        renderClippedPolygon(clippedTri2);
    };

    const auto Clip2 = [this](VSO& v0, VSO& v1, VSO& v2)
    {
        const float alpha0 = (-v0.pos.z) / (v2.pos.z - v0.pos.z);
        const float alpha1 = (-v1.pos.z) / (v2.pos.z - v1.pos.z);

        v0 = Math::linearInterpolation(v0, v2, alpha0);
        v1 = Math::linearInterpolation(v1, v2, alpha1);

        Triangle<VSO> clippedTri( v0, v1, v2 );

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

void RenderPipeline::renderClippedPolygon( Triangle<VSO>& polygon ) 
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

void RenderPipeline::perspectiveDivide( VSO& vso ) const
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

void RenderPipeline::viewport( VSO& vso ) const
{
    vso.pos.x = ( vso.pos.x + 1 ) * m_viewport.width * 0.5f + m_viewport.topLeftX;
    vso.pos.y = ( 1 - vso.pos.y ) * m_viewport.height * 0.5f + m_viewport.topLeftY;
}

} // namespace core
