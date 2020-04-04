#pragma once
#include "PointLightShaderBase.h"

struct PhongShader : public PointLightShaderBase
{
    inline vs_output vertexShader(const vertex& v) override
    {
        vs_output out(v);

        out.posWorld = v4(v.pos) * model;
        out.posView = out.posWorld * view;
        out.pos = out.posView * proj;
        out.n = (v.n * model).getNormalized();

        return out;
    }

    inline v4 pixelShader(const vs_output& interpolated) override
    {
        float intensity = calcIntensityOfPointLightSource(interpolated.posWorld,
                                                          interpolated.n);
        intensity = core::clampNormalize(intensity);

        v2i uv = getTexelCoordinates(interpolated.uv);
        v4 out = getTexelColor(uv);
        out = (out * intensity + ambient).saturate();

        return out;
    }
};