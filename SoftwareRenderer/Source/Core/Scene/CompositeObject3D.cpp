#include "CompositeObject3D.h"

namespace core {

void CompositeObject3D::render(const ICamera& camera) const
{
    for (const auto& component : m_components) 
    {
        component.second->render(camera);
    }
}

void CompositeObject3D::update(unsigned int deltaTime) 
{
    for (auto& component : m_components)
    {
        component.second->update(deltaTime);
    }
}

void CompositeObject3D::move(const Vec3& delta) 
{
    for (const auto& component : m_components)
    {
        component.second->move(delta);
    }
}

void CompositeObject3D::rotate(const Vec3& angles) 
{
    for (const auto& component : m_components)
    {
        component.second->rotate(angles);
    }
}

void CompositeObject3D::scale(const Vec3& scale) 
{
    for (const auto& component : m_components)
    {
        component.second->scale(scale);
    }
}

void CompositeObject3D::setPosition(const Vec3& position) 
{
    m_transform.setPosition(position);
    for (const auto& component : m_components)
    {
        component.second->move(position);
    }
}

void CompositeObject3D::setRotation(const Vec3& angles) 
{
    m_transform.setRotation(angles);
    for (const auto& component : m_components)
    {
        component.second->setRotation(angles);
    }
}

void CompositeObject3D::setScale(const Vec3& scale) 
{
    m_transform.setScale(scale);
    for (const auto& component : m_components)
    {
        component.second->setScale(scale);
    }
}

void CompositeObject3D::addComponent(std::string name,
                                     std::shared_ptr<Object3DBase> component)
{
    m_components.push_back(Component{ name, component });
}

void CompositeObject3D::removeComponent(const std::string& name)
{
    throw std::exception("Not implemented yet");
}

} // namespace core