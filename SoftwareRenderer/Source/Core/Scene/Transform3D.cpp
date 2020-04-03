#include "Transform3D.h"

namespace core {

Transform3D::Transform3D()
    :
    m_scale(Vec3(1.0f, 1.0f, 1.0f))
{
    update();
}

void Transform3D::move(const Vec3& delta)
{
    m_position += delta;
    registerTransformation(_TransformationType::Translation);
}

void Transform3D::rotate(const Vec3& delta)
{
    m_rotation += delta;
    registerTransformation(_TransformationType::Rotation);
}

void Transform3D::scale(const Vec3& delta)
{
    m_scale = m_scale.getHadamard(delta);
    registerTransformation(_TransformationType::Scaling);
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

void Transform3D::setPosition(const Vec3& position)
{
    m_position = position;
    registerTransformation(_TransformationType::Translation);
}

void Transform3D::setRotation(const Vec3& angles)
{
    m_rotation = angles;
    registerTransformation(_TransformationType::Rotation);
}

void Transform3D::setScale(const Vec3& scale)
{
    if (scale.x <= 0.0f)
        m_scale.x = 0.0001f;
    else
        m_scale.x = scale.x;

    if (scale.y <= 0.0f)
        m_scale.y = 0.0001f;
    else
        m_scale.y = scale.y;

    if (scale.z <= 0.0f)
        m_scale.z = 0.0001f;
    else
        m_scale.z = scale.z;

    registerTransformation(_TransformationType::Scaling);
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

void Transform3D::modifyMatrix(_TransformationType matrixType, const Mat4& multiplier)
{
    switch (matrixType)
    {
    case _TransformationType::Translation:
        m_translationMatrix *= multiplier;
        m_isTranslated = true;
        break;
    case _TransformationType::Rotation:
        m_rotationMatrix *= multiplier;
        m_isRotated = true;
        break;
    case _TransformationType::Scaling:
        m_scaleMatrix *= multiplier;
        m_isScaled = true;
        break;
    default:
        break;
    }

    m_isTransformed = true;
}

void Transform3D::registerTransformation(_TransformationType transformationType)
{
    switch (transformationType)
    {
    case _TransformationType::Translation:
        m_isTranslated = true;
        break;
    case _TransformationType::Rotation:
        m_isRotated = true;
        break;
    case _TransformationType::Scaling:
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