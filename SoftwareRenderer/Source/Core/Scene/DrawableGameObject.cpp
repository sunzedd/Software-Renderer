#include "DrawableGameObject.h"

namespace core
{

DrawableGameObject::DrawableGameObject(std::shared_ptr<ShaderProgram> shader)
    :
    GameObject(),
    m_shader(shader)
{
}

DrawableGameObject::DrawableGameObject(std::shared_ptr<ShaderProgram> shader,
                                       const Vec3& position,
                                       const Vec3& rotation,
                                       const Vec3& scale)
    :
    GameObject(position, rotation, scale),
    m_shader(shader)
{
}

void DrawableGameObject::setShader(std::shared_ptr<ShaderProgram> shader)
{
    if (shader)
        m_shader = shader;
}

void DrawableGameObject::setTexture(std::shared_ptr<const sf::Image> texture)
{
    if (texture)
        m_texture = texture;
}

void DrawableGameObject::setMesh(std::shared_ptr<const Mesh> mesh)
{
    m_mesh = mesh;
}

std::shared_ptr<ShaderProgram> DrawableGameObject::getShader()
{
    return m_shader;
}

void DrawableGameObject::update(unsigned int deltaTime)
{
    if (m_isTransformed)
    {
        recalculateModelMatrix();
        m_isTransformed = false;
    }
}

void DrawableGameObject::render(CameraBase& camera)
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