#include "Group3D.h"

namespace core {

void Group3D::render(ICamera& camera)
{
    for (auto& child : m_children)
    {
        child->render(camera);
    }
}

void Group3D::update(unsigned int deltaTime)
{
    for (auto& child : m_children)
    {
        child->update(deltaTime);
    }
}

void Group3D::addChild(std::shared_ptr<Object3D> child)
{
    child->setShader(m_shader);
    child->setTexture(m_texture);
    m_children.push_back(child);
}

} // namespace core