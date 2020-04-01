#pragma once
#include "../../Core/Graphics/ShaderProgram.h"

using v3 = core::Vec3;
using v4 = core::Vec4;
using v2 = core::Vec2;
using v2i = core::Vec2i;
using vs_output = core::VSO;
using vertex = core::Vertex;

class GouraudTextureShader : public core::ShaderProgram
{
public:
    struct Attenuation
    {
        float constant = 1.0f;
        float linear = 0.019f;
        float quadratic = 0.382f;
    };

public:
    Attenuation attenuation;
    float basicIntencity = 0.15f;
    v4 ambient = { 0.25f, 0.25f, 0.25f, 0.25f };
    v3 pointLightPosition = { 0.0f, 2.0f, 0.0f };
    v3 directionLightDirection = { -1.0f, -1.0f, -1.0f };

public:
    inline vs_output vertexShader(const vertex& v) override
    {
        vs_output out(v);
        out.intensity = basicIntencity;

        // vertex transformations
        out.posWorld = v4(v.pos) * model;
        out.posView = out.posWorld * view;
        out.pos = out.posView * proj;
        out.n = (v.n * model).getNormalized();

        // lighting calculation
        v3 lightDirection = v3(out.posWorld) - pointLightPosition;
        float distanceToLight = lightDirection.length();
        lightDirection.normalize();

        float attenuationFactor = 1.0f / (
            attenuation.constant +
            attenuation.linear * distanceToLight +
            attenuation.quadratic * distanceToLight * distanceToLight);

        out.intensity += calcIntesity(out.n, lightDirection) * attenuationFactor;
        out.intensity = core::clampNormalize(out.intensity);

        return out;
    }

    inline v4 pixelShader(const vs_output& interpolated) override
    {
        const int tex_width = m_texture->getSize().x;
        const int tex_height = m_texture->getSize().y;

        v2 uv = clampUV(interpolated.uv);
        v2i uvi = getTexelCoordinates(uv);

        sf::Color texel = m_texture->getPixel(uvi.x, uvi.y);
        v4 texel_v4 = { (float)texel.r, (float)texel.g, (float)texel.b, (float)texel.a };
        texel_v4 /= 255.0f;

        v4 out_color = (texel_v4 * interpolated.intensity + ambient).saturate();
    
        return out_color;
    }
};