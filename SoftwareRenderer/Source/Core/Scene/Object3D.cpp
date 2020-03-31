#include "../Graphics/RenderPipeline.h"
#include "Object3D.h"

namespace core {

void Object3D::render(const ICamera& camera)
{
    auto& renderer = RenderPipeline::instance();

    if (m_renderMode == RenderMode::WIREFRAME)
        renderer.toogleWireframeRendering(true);
    if (m_rejectBackFaces)
        renderer.toogleBackFaceCulling(m_rejectBackFaces);
    
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

} // namespace core