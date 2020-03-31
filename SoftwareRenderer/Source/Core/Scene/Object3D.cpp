#include "../Graphics/RenderPipeline.h"
#include "Object3D.h"

namespace core {

void Object3D::render(ICamera& camera)
{
    auto& renderer = RenderPipeline::instance();

    if (m_renderMode == RenderMode::WIREFRAME) 
        renderer.toogleWireframeRendering(true);
    
    if (m_rejectBackFaces)                     
        renderer.toogleBackFaceCulling(m_rejectBackFaces);

    m_shader->bindModelMatrix(m_transform.getModelMatrix());
    m_shader->bindViewMatrix(camera.getViewMatrix());
    m_shader->bindProjectionMatrix(camera.getProjMatrix());

    renderer.bindShaderProgram(m_shader);
    renderer.drawFaces(m_mesh->faces());
    renderer.toogleWireframeRendering(false);
}

void Object3D::update(unsigned int deltaTime)
{
    m_transform.update();
}

std::shared_ptr<ShaderProgram> Object3D::getShader()
{
    return m_shader;
}

const std::shared_ptr<Mesh>& Object3D::getMesh() const
{
    return m_mesh;
}

const std::shared_ptr<sf::Image>& Object3D::getTexture() const
{
    return m_texture;
}

void Object3D::setShader(std::shared_ptr<ShaderProgram> shader) 
{
    if (shader)
        m_shader = shader;
}

void Object3D::setMesh(std::shared_ptr<Mesh> mesh) 
{
    if (mesh)
        m_mesh = mesh;
}

void Object3D::setTexture(std::shared_ptr<sf::Image> texture)
{
    if (!m_shader)
        throw IncorrectOperationOrder("Set shader before setting a texture.");

    if (texture)
        m_texture = texture;

    m_shader->bindTexture(m_texture);
}

} // namespace core