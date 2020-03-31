#include "Transform3D.h"

namespace core {

Transform3D::Transform3D()
    :
    m_scale(1.0f, 1.0f, 1.0f),
    m_isTransformed(false)
{
    update();
}

const Vec3& Transform3D::getPosition() const 
{
    return m_position;
}

const Vec3& Transform3D::getRotation() const 
{
    return m_rotation;
}

const Vec3& Transform3D::getScale() const 
{
    return m_scale;
}

const Mat4& Transform3D::getModelMatrix() const
{
    return m_modelMatrix;
}

const Mat4& Transform3D::getTranslationMatrix() const
{
    return m_translationMatrix;
}

const Mat4& Transform3D::getRotationMatrix() const
{
    return m_rotationMatrix;
}

const Mat4& Transform3D::getScaleMatrix() const
{
    return m_scaleMatrix;
}

void Transform3D::setPosition(const Vec3& position)
{
    m_position = position;
    registerTransformation(TransformationType::TRANSLATION);
}

void Transform3D::setRotation(const Vec3& rotation)
{
    m_rotation = rotation;
    registerTransformation(TransformationType::ROTATION);
}

void Transform3D::setScale(const Vec3& scale) 
{
    if (scale.x <= 0.0f)
        m_scale.x = 0.0001f;
    if (scale.y <= 0.0f)
        m_scale.y = 0.0001f;
    if (scale.z <= 0.0f)
        m_scale.z = 0.0001f;
    registerTransformation(TransformationType::SCALE);
}

void Transform3D::move(const Vec3& delta) 
{
    m_position += delta;
    registerTransformation(TransformationType::TRANSLATION);
}

void Transform3D::rotate(const Vec3& delta) 
{
    m_rotation += delta;
    registerTransformation(TransformationType::ROTATION);
}

void Transform3D::scale(const Vec3& delta) 
{
    m_scale = m_scale.getHadamard(delta);
    registerTransformation(TransformationType::SCALE);
}

void Transform3D::update() 
{
    if (m_isTransformed)
    {
        if (m_isTranslated) m_translationMatrix = Mat4::translation(m_position);
        if (m_isRotated) m_rotationMatrix = Mat4::rotationXYZ(m_rotation);
        if (m_isScaled) m_scaleMatrix = Mat4::scale(m_scale);

        m_modelMatrix = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;
    }

    resetTransformationFlags();
}

void Transform3D::registerTransformation(TransformationType type)
{
    switch (type)
    {
    case TransformationType::TRANSLATION:
        m_isTransformed = true;
        break;
    case TransformationType::ROTATION:
        m_isRotated = true;
        break;
    case TransformationType::SCALE:
        m_isScaled = true;
        break;
    default:
        break;
    }

    m_isTransformed = true;
}

void Transform3D::resetTransformationFlags()
{
    m_isRotated = false;
    m_isTranslated = false;
    m_isScaled = false;
    m_isTransformed = false;
}

} // namespace core