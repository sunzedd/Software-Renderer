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
    return normal.dot(-lightDirection.normalized());
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
