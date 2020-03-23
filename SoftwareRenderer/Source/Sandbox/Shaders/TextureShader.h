#pragma once
#include "../../Core/Graphics/ShaderProgram.h"

class TextureShader : public core::ShaderProgram
{
public:
    core::VSO vertexShader(const core::Vertex& v) override
    {
        using namespace core;
    
        VSO out(v);

        out.posWorld = Vec4(v.pos) * model;
        out.posView = out.posWorld * view;
        out.pos = out.posView * proj;

        out.n = v.n * model;
        out.intensity = calcIntesity(out.n, Vec3(0, 0, -1));

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

        const int texsel_x = m_texture->getSize().x * uv_x - 1;
        const int texsel_y = m_texture->getSize().y * uv_y - 1;

        sf::Color texel = m_texture->getPixel(texsel_x, texsel_y);
        Vec4 texel_v4 =
        {
            (float)texel.r / 255.0f,
            (float)texel.g / 255.0f,
            (float)texel.b / 255.0f,
            (float)texel.a / 255.0f
        };

        Vec4 out = (texel_v4 * interpolated.intensity).saturate();

        return out;
    }
};