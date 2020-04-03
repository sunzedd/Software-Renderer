#include "Object3D.h"

namespace core {

void Object3D::render(const ICamera& camera) const
{
    auto& renderer = RenderPipeline::instance();

    m_shader->bindModelMatrix(m_transform.getModelMatrix());
    m_shader->bindTexture(m_texture);
    m_shader->bindViewMatrix(camera.getViewMatrix());
    m_shader->bindProjectionMatrix(camera.getProjMatrix());

    renderer.bindShaderProgram(m_shader);
    m_mesh->render();
}

void Object3D::update(unsigned int deltaTime)
{
    m_transform.update();
}

void Object3D::move(const Vec3& delta) 
{
    m_transform.move(delta);
}

void Object3D::rotate(const Vec3& angles)
{
    m_transform.rotate(angles);
}

void Object3D::scale(const Vec3& scale) 
{
    m_transform.scale(scale);
}

void Object3D::setPosition(const Vec3& position) 
{
    m_transform.setPosition(position);
}

void Object3D::setRotation(const Vec3& angles) 
{
    m_transform.setRotation(angles);
}

void Object3D::setScale(const Vec3& scale)
{
    m_transform.setScale(scale);
}

void Object3D::setShader(std::shared_ptr<ShaderProgram> shader)
{
    if (shader)
        m_shader = shader;
}

void Object3D::setMesh(std::shared_ptr<const Mesh> mesh)
{
    if (mesh)
        m_mesh = mesh;
}

void Object3D::setTexture(std::shared_ptr<const sf::Image> texture)
{
    if (texture)
        m_texture = texture;
}

} // namespace core