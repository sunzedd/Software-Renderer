#include "PointLight.h"

namespace core {

PointLight::PointLight()
    :
    DrawableGameObject(std::make_shared<PointLight::Shader>(this)),
    m_indicatorColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_indicatorIntensity(1.0f)
{
    m_mesh = AssetLoader::loadMesh("Assets\\Meshes\\sphere.obj");
}

PointLight::PointLight(const Vec3& position,const Vec3& scale)
    :
    DrawableGameObject(std::make_shared<PointLight::Shader>(this), position, scale),
    m_indicatorColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_indicatorIntensity(1.0f)
{
    m_mesh = AssetLoader::loadMesh("Assets\\Meshes\\sphere.obj");
}

void PointLight::toggleVisibility(bool enabled)
{
    m_isVisible = enabled;
}

void PointLight::setIndicatorColor(const Vec4& color)
{
    m_indicatorColor = color;
}

void PointLight::setIndicatorIntensity(float intensity)
{
    m_indicatorIntensity = intensity;
}

void PointLight::setAttenuationCoefs(float constant, float linear, float quadratic)
{
    m_attenuation.constant = constant;
    m_attenuation.linear = linear;
    m_attenuation.quadratic = quadratic;
}

const PointLight::AttenuationCoefs& PointLight::getAttenuation()
{
    return m_attenuation;
}

void PointLight::update(unsigned int deltaTime)
{
    if (m_isVisible && m_isTransformed)
    {
        recalculateModelMatrix();
        m_isTransformed = false;
    }
}

void PointLight::render(CameraBase& camera)
{
    if (m_isVisible)
    {
        RenderPipeline& renderer = RenderPipeline::instance();

        m_shader->bindModelMatrix(m_transformMatrices.model);
        m_shader->bindViewMatrix(camera.getViewMatrix());
        m_shader->bindProjectionMatrix(camera.getProjMatrix());
        m_shader->bindTexture(m_texture);

        renderer.bindShaderProgram(m_shader);

        m_mesh->render();
    }
}

PointLight::Shader::Shader(PointLight* owner)
    :
    m_owner(owner)
{
}

VSO PointLight::Shader::vertexShader(const Vertex& v)
{
    VSO out(v);

    out.posWorld = Vec4(v.pos) * model;
    out.posView = out.posWorld * view;
    out.pos = out.posView * proj;

    return out;
}

Vec4 PointLight::Shader::pixelShader(const VSO& interpolated)
{
    return  m_owner->m_indicatorColor * m_owner->m_indicatorIntensity;
}

} // namespace core