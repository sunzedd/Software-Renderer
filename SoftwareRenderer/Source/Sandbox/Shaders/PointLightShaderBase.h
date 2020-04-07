#pragma once
#include "../../Core/Utils.h"
#include "Aliases.h"

struct PointLightShaderBase : public core::Shader
{
    struct Attenuation
    {
        float constant = 0.5f;
        float linear = 0.019f;
        float quadratic = 0.082f;
    };

    Attenuation attenuation;
    v4 ambient = { 0.05f, 0.05f, 0.05f, 1.0f };
    v3 pointLightSourcePosition;

    inline float calcIntensityOfPointLightSource(const v4& vertexWorldPosition,
                                               const v4& normal)
    {
        v3 lightDirection = v3(vertexWorldPosition) - pointLightSourcePosition;
        const float distanceToSource = lightDirection.length();
        lightDirection.normalize();

        float attenuationFactor = 1.0f / (
            attenuation.constant +
            attenuation.linear * distanceToSource +
            attenuation.quadratic * distanceToSource * distanceToSource);

        return core::clampNormalize(
            calcIntesity(normal, lightDirection) * attenuationFactor);
    }

    virtual inline vs_output vertexShader(const vertex& v) = 0;
    virtual inline color pixelShader(const vs_output& interpolated) = 0;
};

