#include "Shader.h"

namespace core {


// --------------------------------------------------------------------------------------
//                            class Shader
//---------------------------------------------------------------------------------------
void Shader::bindModelMatrix(const Mat4& m)
{
    model = m;
}

void Shader::bindViewMatrix(const Mat4& m)
{
    view = m;
}

void Shader::bindProjectionMatrix(const Mat4& m)
{
    proj = m;
}

void Shader::bindTexture(std::shared_ptr<const sf::Image> texture)
{
    if (texture)
        m_texture = texture;
}

float Shader::calcIntesity(const Vec3& normal, const Vec3& lightDirection) const
{
    return std::max(0.0f, normal.dot(-lightDirection.normalized()));
}

Vec2 Shader::clampUV(const Vec2& uv)
{
    Vec2 clamped;
    clamped.x = clampNormalize(uv.x);
    clamped.y = clampNormalize(uv.y);

    return clamped;
}

Vec2i Shader::getTexelCoordinates(const Vec2& uv)
{
    Vec2i texel;
    const int textureWidth = m_texture->getSize().x;
    const int textureHeight = m_texture->getSize().y;

    texel.x = uv.x * textureWidth;
    texel.y = uv.y * textureHeight;

    if (texel.x == textureWidth)  texel.x--;
    if (texel.y == textureHeight) texel.y--;

    return texel;
}

Vec4 Shader::getTexelColor(const Vec2i& uv)
{
    sf::Color texel = m_texture->getPixel(uv.x, uv.y);

    Vec4 texel_v4 = { 
        (float)texel.r,
        (float)texel.g,
        (float)texel.b,
        (float)texel.a 
    };

    texel_v4 /= 255.0f;

    return texel_v4;
}


// --------------------------------------------------------------------------------------
//                            class Shader::Default
//---------------------------------------------------------------------------------------
VertexShaderOut Shader::Default::vertexShader(const Vertex& v)
{
    VertexShaderOut out(v);
    out.pos = out.pos * model * view * proj;
    out.intensity = 1.0f;

    return out;
}

Color Shader::Default::pixelShader(const VertexShaderOut& interpolated)
{
    return m_defaultColor;
}




// --------------------------------------------------------------------------------------
//                            class VertexShaderOut
//---------------------------------------------------------------------------------------
VertexShaderOut::VertexShaderOut(const Vertex& v)
{
    pos = v.pos;
    n = v.n;
    uv = v.uv;
    color = v.color;

    intensity = 0.0f;
}

VertexShaderOut& VertexShaderOut::operator += (const VertexShaderOut& rhs)
{
    pos += rhs.pos;
    n += rhs.n;
    uv += rhs.uv;
    color += rhs.color;
    posWorld += rhs.posWorld;
    posView += rhs.posView;
    intensity += rhs.intensity;

    return *this;
}

VertexShaderOut& VertexShaderOut::operator -= (const VertexShaderOut& rhs)
{
    pos -= rhs.pos;
    n -= rhs.n;
    uv -= rhs.uv;
    color -= rhs.color;
    posWorld -= rhs.posWorld;
    posView -= rhs.posView;
    intensity -= rhs.intensity;

    return *this;
}

VertexShaderOut& VertexShaderOut::operator *= (float val)
{
    pos *= val;
    n *= val;
    uv *= val;
    color *= val;
    posWorld *= val;
    posView *= val;
    intensity *= val;

    return *this;
}

VertexShaderOut& VertexShaderOut::operator /= (float val)
{
    pos /= val;
    n /= val;
    uv /= val;
    color /= val;
    posWorld /= val;
    posView /= val;
    intensity /= val;

    return *this;
}

VertexShaderOut operator + (const VertexShaderOut& lhs, const VertexShaderOut& rhs)
{
    VertexShaderOut out(lhs);
    out += rhs;

    return out;
}

VertexShaderOut operator - (const VertexShaderOut& lhs, const VertexShaderOut& rhs)
{
    VertexShaderOut out(lhs);
    out -= rhs;

    return out;
}

VertexShaderOut operator * (const VertexShaderOut& vso, float val)
{
    VertexShaderOut out(vso);
    out *= val;

    return out;
}

VertexShaderOut operator / (const VertexShaderOut& vso, float val)
{
    VertexShaderOut out(vso);
    out /= val;

    return out;
}

} // namespace core
