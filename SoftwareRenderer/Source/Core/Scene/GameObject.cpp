#include "GameObject.h"

namespace core
{

GameObject::GameObject()
{}

GameObject::GameObject(const Vec3& position, const Vec3& rotation, const Vec3& scale)
{
    m_transform.position = position;
    m_transform.rotation = rotation;
    m_transform.scale;
}

Transform& GameObject::getTransform()
{
    m_isTransformed = true;
    return m_transform;
}

void GameObject::recalculateModelMatrix()
{
    if (m_isTransformed)
    {
        m_transformMatrices.translation = Mat4::translation(m_transform.position);
        m_transformMatrices.rotation = Mat4::rotationXYZ(m_transform.rotation);
        m_transformMatrices.scale = Mat4::scale(m_transform.scale);

        m_transformMatrices.model = m_transformMatrices.scale *
                                    m_transformMatrices.rotation *
                                    m_transformMatrices.translation;
        m_isTransformed = false;
    }
}

}