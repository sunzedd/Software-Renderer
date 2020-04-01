#include "ShaderProgram.h"

namespace core {


// --------------------------------------------------------------------------------------
//                            class ShaderProgram
//---------------------------------------------------------------------------------------
void ShaderProgram::bindModelMatrix(const Mat4& m)
{
    model = m;
}

void ShaderProgram::bindViewMatrix(const Mat4& m)
{
    view = m;
}

void ShaderProgram::bindProjectionMatrix(const Mat4& m)
{
    proj = m;
}

void ShaderProgram::bindTexture(std::shared_ptr<const sf::Image> texture)
{
    if (texture)
        m_texture = texture;
}

float ShaderProgram::calcIntesity(const Vec3& normal, const Vec3& lightDirection) const
{
    return std::max(0.0f, normal.dot(-lightDirection.normalized()));
}

Vec2 ShaderProgram::clampUV(const Vec2& uv)
{
    Vec2 clamped;
    clamped.x = clampNormalize(uv.x);
    clamped.y = clampNormalize(uv.y);

    return clamped;
}

Vec2i ShaderProgram::getTexelCoordinates(const Vec2& uv)
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

Vec4 ShaderProgram::getTexelColor(const Vec2i& uv)
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
//                            class ShaderProgram::Default
//---------------------------------------------------------------------------------------
VSO ShaderProgram::Default::vertexShader(const Vertex& v)
{
    VSO out(v);
    out.pos = out.pos * model * view * proj;
    out.intensity = 1.0f;

    return out;
}

Vec4 ShaderProgram::Default::pixelShader(const VSO& interpolated)
{
    return m_defaultColor;
}




// --------------------------------------------------------------------------------------
//                            class VSO
//---------------------------------------------------------------------------------------
VSO::VSO(const Vertex& v)
{
    pos = v.pos;
    n = v.n;
    uv = v.uv;
    color = v.color;

    intensity = 0.0f;
}

VSO& VSO::operator += (const VSO& rhs)
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

VSO& VSO::operator -= (const VSO& rhs)
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

VSO& VSO::operator *= (float val)
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

VSO& VSO::operator /= (float val)
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

VSO operator + (const VSO& lhs, const VSO& rhs)
{
    VSO out(lhs);
    out += rhs;

    return out;
}

VSO operator - (const VSO& lhs, const VSO& rhs)
{
    VSO out(lhs);
    out -= rhs;

    return out;
}

VSO operator * (const VSO& vso, float val)
{
    VSO out(vso);
    out *= val;

    return out;
}

VSO operator / (const VSO& vso, float val)
{
    VSO out(vso);
    out /= val;

    return out;
}

} // namespace core
