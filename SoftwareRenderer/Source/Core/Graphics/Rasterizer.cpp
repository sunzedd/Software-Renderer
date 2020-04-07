#include "Rasterizer.h"

namespace core {

Rasterizer::Rasterizer(FrameBuffer& frameBuf)
    :
    m_frameBuf(frameBuf ),
    m_depthBuf(frameBuf.width(), frameBuf.height())
{ }

void Rasterizer::clearBuffers()
{
    m_depthBuf.clear();
    m_frameBuf.clear();
}

void Rasterizer::bindShaderProgram(std::shared_ptr<ShaderProgram> shader)
{
    m_shader = shader;
}

void Rasterizer::line(const Vec2& p0, const Vec2& p1, const Color& color)
{
    int x1 = static_cast<int>( p0.x );
    int y1 = static_cast<int>( p0.y );
    int x2 = static_cast<int>( p1.x );
    int y2 = static_cast<int>( p1.y );

    bool steep = false;
    if( std::abs(x1 - x2) < std::abs(y1 - y2) )
    {
        std::swap( x1, y1 );
        std::swap( x2, y2 );
        steep = true;
    }

    if( x1 > x2 ) 
    {
        std::swap( x1, x2 );
        std::swap( y1, y2 );
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y1;

    for( int x = x1; x <= x2; x++ )
    {
        if ( steep )
        {
            m_frameBuf.setPixel( y, x, color);
        }
        else
            m_frameBuf.setPixel( x, y, color);

        error2 += derror2;
        if( error2 > dx )
        {
            y += ( y2 > y1 ? 1 : -1 );
            error2 -= dx * 2;
        }
    }
}

void Rasterizer::line(const Vec3& p0, const Vec3& p1, const Color& color)
{
    int x1 = static_cast<int>(p0.x);
    int y1 = static_cast<int>(p0.y);
    int x2 = static_cast<int>(p1.x);
    int y2 = static_cast<int>(p1.y);

    bool steep = false;
    if (std::abs(x1 - x2) < std::abs(y1 - y2))
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }

    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y1;

    for (int x = x1; x <= x2; x++)
    {
        if (steep)
        {
            m_frameBuf.setPixel(y, x, color);
        }
        else
            m_frameBuf.setPixel(x, y, color);

        error2 += derror2;
        if (error2 > dx)
        {
            y += (y2 > y1 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void Rasterizer::line(VSO& v0, VSO& v1, const Color& color)
{
    const auto& x0 = v0.pos.x;
    const auto& x1 = v1.pos.x;
    const auto& y0 = v0.pos.y;
    const auto& y1 = v1.pos.y;
    

    if ((x0 < 0 || y0 < 0 || x0 > m_frameBuf.width() - 1 || y0 > m_frameBuf.height() - 1) ||
        (x1 < 0 || y1 < 0 || x1 > m_frameBuf.width() - 1 || y1 > m_frameBuf.height() - 1))
        return;

    bool steep = false;
    if (std::abs(v0.pos.x - v1.pos.x) < std::abs(v0.pos.y - v1.pos.y))
    {
        std::swap(v0.pos.x, v0.pos.y);
        std::swap(v1.pos.x, v1.pos.y);
        steep = true;
    }

    if (v0.pos.x > v1.pos.x)
        std::swap(v0.pos, v1.pos);

    int dx = v1.pos.x - v0.pos.x;
    int dy = v1.pos.y - v0.pos.y;
    float dz = v1.pos.w - v0.pos.w;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = v0.pos.y;

    float z = v0.pos.w;
    for (int x = v0.pos.x; x <= v1.pos.x; x++)
    {
        if (steep)
        {
            //if (m_depthBuf.testAndSet(y, x, z)) {
                m_frameBuf.setPixel(y, x, color);
            //}
        }
        else
        {
            //if (m_depthBuf.testAndSet(x, y, z)) {
                m_frameBuf.setPixel(x, y, color);
            //}
        }

        error2 += derror2;
        if (error2 > dx)
        {
            y += (v1.pos.y > v0.pos.y ? 1 : -1);
            error2 -= dx * 2;
        }

        z += dz;
    }
}

void Rasterizer::triangleWireframe(const Vec3& p0, const Vec3& p1, const Vec3& p2,
                                   const Color& color)
{
    line(p0, p1, color);
    line(p1, p2, color);
    line(p2, p0, color);
}

void Rasterizer::triangle(const Triangle<VSO>& triangle)
{
    // using pointers so we can swap (for sorting purposes)
    const VSO* pv0 = &triangle.v0;
    const VSO* pv1 = &triangle.v1;
    const VSO* pv2 = &triangle.v2;

    // sorting vertices by y
    if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
    if (pv2->pos.y < pv1->pos.y) std::swap(pv1, pv2);
    if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);

    if (pv0->pos.y == pv1->pos.y) // natural flat top
    {
        // sorting top vertices by x
        if (pv1->pos.x < pv0->pos.x) std::swap(pv0, pv1);

        triangleFlatTop(*pv0, *pv1, *pv2);
    }
    else if (pv1->pos.y == pv2->pos.y) // natural flat bottom
    {
        // sorting bottom vertices by x
        if (pv2->pos.x < pv1->pos.x) std::swap(pv1, pv2);

        triangleFlatBottom(*pv0, *pv1, *pv2);
    }
    else // general triangle
    {
        // find splitting vertex interpolant
        const float alphaSplit =
            (pv1->pos.y - pv0->pos.y) /
            (pv2->pos.y - pv0->pos.y);

        const auto vi = Math::linearInterpolation(*pv0, *pv2, alphaSplit);

        if (pv1->pos.x < vi.pos.x) // major right
        {
            triangleFlatBottom(*pv0, *pv1, vi);
            triangleFlatTop(*pv1, vi, *pv2);
        }
        else // major left
        {
            triangleFlatBottom(*pv0, vi, *pv1);
            triangleFlatTop(vi, *pv1, *pv2);
        }
    }
}

void Rasterizer::triangleFlatTop(const VSO& it0, const VSO& it1, const VSO& it2)
{
    // calulcate dVertex / dy
    // change in interpolant for every 1 change in y
    const float delta_y = it2.pos.y - it0.pos.y;
    const auto dit0 = (it2 - it0) / delta_y;
    const auto dit1 = (it2 - it1) / delta_y;

    // create right edge interpolant
    auto itEdge1 = it1;

    // call the flat triangle render routine
    triangleFlat(it0, it1, it2, dit0, dit1, itEdge1);
}

void Rasterizer::triangleFlatBottom(const VSO& it0, const VSO& it1, const VSO& it2)
{
    // calulcate dVertex / dy
    // change in interpolant for every 1 change in y
    const float delta_y = it2.pos.y - it0.pos.y;
    const auto dit0 = (it1 - it0) / delta_y;
    const auto dit1 = (it2 - it0) / delta_y;

    // create right edge interpolant
    auto itEdge1 = it0;

    // call the flat triangle render routine
    triangleFlat(it0, it1, it2, dit0, dit1, itEdge1);
}

void Rasterizer::triangleFlat(const VSO& it0, const VSO& it1, const VSO& it2,
                              const VSO& dv0, const VSO& dv1, VSO itEdge1)
{
    auto itEdge0 = it0;

    const int yStart = std::max((int)ceil(it0.pos.y - 0.5f), 0);
    const int yEnd = std::min((int)ceil(it2.pos.y - 0.5f), (int)m_frameBuf.height() - 1);

    itEdge0 += dv0 * (float(yStart) + 0.5f - it0.pos.y);
    itEdge1 += dv1 * (float(yStart) + 0.5f - it0.pos.y);

    for (int y = yStart; y < yEnd; y++, itEdge0 += dv0, itEdge1 += dv1)
    {
        const int xStart = std::max((int)ceil(itEdge0.pos.x - 0.5f), 0);
        const int xEnd = std::min((int)ceil(itEdge1.pos.x - 0.5f), (int)m_frameBuf.width() - 1);

        auto iLine = itEdge0;

        const float dx = itEdge1.pos.x - itEdge0.pos.x;
        const auto diLine = (itEdge1 - iLine) / dx;

        iLine += diLine * (float(xStart) + 0.5f - itEdge0.pos.x);

        for (int x = xStart; x < xEnd; x++, iLine += diLine)
        {
            if (m_depthBuf.testAndSet(x, y, iLine.pos.w))
            {
                // recover interpolated z from interpolated 1/z
                const float w = 1.0f / iLine.pos.w;

                VSO interpolated = iLine;
                interpolated.uv *= w;
                interpolated.color *= w;
                interpolated.intensity *= w;

                m_frameBuf.setPixel(x, y, m_shader->pixelShader(interpolated));
            }
        }
    }
}

} // namespace core
