#pragma once
#include "../Math/Math.h"
#include "../AssetLoader.h"

#include "DrawableGameObject.h"

namespace core {

class PointLight : public DrawableGameObject
{
public:
    struct AttenuationCoefs
    {
        float constant  = 1.0f;
        float linear    = 0.01f;
        float quadratic = 0.002f;
    };

    class Shader;

    PointLight();
    PointLight(const Vec3& position, const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f));

    void toggleVisibility(bool enabled);
    void setIndicatorColor(const Vec4& color);
    void setIndicatorIntensity(float intensity);
    void setAttenuationCoefs(float constant, float linear, float quadratic);

    const AttenuationCoefs& getAttenuation();

    void update(unsigned int deltaTime) override;
    void render(CameraBase& camera) override;

private:
    AttenuationCoefs m_attenuation;
    Vec4 m_indicatorColor;
    float m_indicatorIntensity;
    bool m_isVisible;
};

class PointLight::Shader : public ShaderProgram
{
public:
    Shader(PointLight* owner);

    VSO vertexShader(const Vertex& v) override;
    Vec4 pixelShader(const VSO& interpolated) override;

private:
    PointLight* m_owner;
};

} // namespace core