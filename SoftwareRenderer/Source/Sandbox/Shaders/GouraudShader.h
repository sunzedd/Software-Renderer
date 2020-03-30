#pragma once
#include "../../Core/Graphics/ShaderProgram.h"
#include "../../Core/Scene/PointLight.h"

class GouraudShader : public core::ShaderProgram
{
public:
    core::Vec4 ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
    std::shared_ptr<core::PointLight> pointLight;

public:
    core::VSO vertexShader(const core::Vertex& v) override
    {
        using namespace core;
    
        VSO out(v);

        out.posWorld = Vec4(v.pos) * model;
        out.posView = out.posWorld * view;
        out.pos = out.posView * proj;

        out.n = v.n * model;

        Vec3 lightDirection = Vec3(out.posWorld) - pointLight->getTransform().position;
        float distanceToLight = lightDirection.length();
        lightDirection.normalize();

        float attenuationFactor = 1.0f / (
            pointLight->getAttenuation().constant +
            pointLight->getAttenuation().linear * distanceToLight +
            pointLight->getAttenuation().quadratic * distanceToLight * distanceToLight
            );

        out.intensity = calcIntesity(out.n, lightDirection);
        out.intensity *= attenuationFactor;

        return out;
    }

    core::Vec4 pixelShader(const core::VSO& interpolated) override
    {
        using namespace core;

        // clamp texture
        float uv_x = std::max(0.0f, interpolated.uv.x);
        float uv_y = std::max(0.0f, interpolated.uv.y);
        uv_x = std::min(uv_x, 1.0f);
        uv_y = std::min(uv_y, 1.0f);

        const int texsel_x = m_texture->getSize().x * uv_x;
        const int texsel_y = m_texture->getSize().y * uv_y;

        sf::Color texel = m_texture->getPixel(texsel_x, texsel_y);
        Vec4 texel_v4 =
        {
            (float)texel.r / 255.0f,
            (float)texel.g / 255.0f,
            (float)texel.b / 255.0f,
            (float)texel.a / 255.0f
        };

        Vec4 out = (texel_v4 * interpolated.intensity + ambient).saturate();

        return out;
    }
};