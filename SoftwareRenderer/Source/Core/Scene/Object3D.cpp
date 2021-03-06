#include "Object3D.h"

namespace core {

Object3D::Object3D()
{
    m_mesh = AssetLoader::loadDefaultMesh();
    m_texture = AssetLoader::loadDefaultImage();
    m_shader = std::make_shared<Shader::Default>();
}

void Object3D::render(const ICamera& camera) const
{
    auto* renderer = Renderer::getRendererInstance();

    m_shader->bindModelMatrix(m_transform.getModelMatrix());
    m_shader->bindTexture(m_texture);
    m_shader->bindViewMatrix(camera.getViewMatrix());
    m_shader->bindProjectionMatrix(camera.getProjMatrix());

    renderer->bindShader(m_shader);
    m_mesh->render();
}

void Object3D::update(unsigned int deltaTime)
{
    m_transform.update();

    if (m_script)
        m_script->update(deltaTime);
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

void Object3D::setShader(std::shared_ptr<Shader> shader)
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

void Object3D::setAttributes(std::shared_ptr<Shader> shader,
                             std::shared_ptr<const Mesh> mesh,
                             std::shared_ptr<const sf::Image> texture)
{
    setShader(shader);
    setMesh(mesh);
    setTexture(texture);
}

void Object3D::setAttributes(std::shared_ptr<Shader> shader,
                             std::shared_ptr<const Mesh> mesh)
{
    setShader(shader);
    setMesh(mesh);
}

} // namespace core