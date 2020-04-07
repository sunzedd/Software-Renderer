#pragma once
#include <memory>
#include <SFML/Graphics/Image.hpp>

#include "../Utils.h"

#include "Vertex.h"
#include "Color.h"

namespace core {

class VertexShaderOut;

class Shader
{
public:
    class Default;

public:
    static std::shared_ptr<Default> createDefaultShader() {
        return std::make_shared<Default>();
    }

    virtual VertexShaderOut vertexShader(const Vertex& v) = 0;
    virtual Color pixelShader(const VertexShaderOut& interpolated) = 0;

    void bindModelMatrix(const Mat4& m);
    void bindViewMatrix(const Mat4& m);
    void bindProjectionMatrix(const Mat4& m);

    void bindTexture(std::shared_ptr<const sf::Image> texture);

protected:
    float calcIntesity(const Vec3& normal, const Vec3& lightDirection) const;
    Vec2 clampUV(const Vec2& uv);
    Vec2i getTexelCoordinates(const Vec2& uv);
    Vec4 getTexelColor(const Vec2i& uv);

protected:
    Mat4 model;
    Mat4 view;
    Mat4 proj;
    std::shared_ptr<const sf::Image> m_texture;
};


class Shader::Default : public Shader
{
public:
    virtual VertexShaderOut vertexShader(const Vertex& v) override;
    virtual Color pixelShader(const VertexShaderOut& interpolated) override;
private:
    const Color m_defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f };
};

struct VertexShaderOut
{
    Vec4 pos;
    Vec4 n;
    Vec2 uv;
    Color color;

    Vec4 posWorld;
    Vec4 posView;
    float intensity;

    VertexShaderOut(const Vertex& v);

    VertexShaderOut& operator += (const VertexShaderOut& rhs);
    VertexShaderOut& operator -= (const VertexShaderOut& rhs);
    VertexShaderOut& operator *= (float val);
    VertexShaderOut& operator /= (float val);

    friend VertexShaderOut operator + (const VertexShaderOut& lhs, const VertexShaderOut& rhs);
    friend VertexShaderOut operator - (const VertexShaderOut& lhs, const VertexShaderOut& rhs);
    friend VertexShaderOut operator * (const VertexShaderOut& vso, float val);
    friend VertexShaderOut operator / (const VertexShaderOut& vso, float val);
};

} // namespace core
