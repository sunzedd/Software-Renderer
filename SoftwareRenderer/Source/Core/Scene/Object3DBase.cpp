#include "Object3DBase.h"

namespace core {

void Object3DBase::attachScript(Script* script)
{
    m_script.reset(script);
    m_script->init(this);
}

void Object3DBase::toggleVisibility(bool enable) 
{
    m_isVisible = enable;
}

void Object3DBase::toggleActivity(bool enable) 
{
    m_isActive = enable;
}

bool Object3DBase::isActive() const 
{
    return m_isActive;
}

bool Object3DBase::isVisible() const 
{
    return m_isVisible;
}

bool Object3DBase::hasScript() const
{
    return (bool)m_script;
}

const Vec3& Object3DBase::getPosition() const 
{
    return m_transform.getPosition();
}

const Vec3& Object3DBase::getRotation() const 
{
    return m_transform.getRotation();
}

const Vec3& Object3DBase::getScale() const 
{
    return m_transform.getScale();
}

} // namespace core