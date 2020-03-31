#pragma once
#include "../Math/Math.h"

namespace core {

class Transform3D
{
    enum class TransformationType
    {
        TRANSLATION,
        ROTATION,
        SCALE
    };

public:
    Transform3D();

    const Vec3& getPosition() const;
    const Vec3& getRotation() const;
    const Vec3& getScale() const;

    const Mat4& getModelMatrix() const;
    const Mat4& getTranslationMatrix() const;
    const Mat4& getRotationMatrix() const;
    const Mat4& getScaleMatrix() const;

    void setPosition(const Vec3& position);
    void setRotation(const Vec3& rotation);
    void setScale(const Vec3& scale);

    void move(const Vec3& delta);
    void rotate(const Vec3& delta);
    void scale(const Vec3& delta);

    void update();

private:
    void registerTransformation(TransformationType type);
    void resetTransformationFlags();

private:
    Vec3 m_position;
    Vec3 m_rotation;
    Vec3 m_scale;

    Mat4 m_translationMatrix;
    Mat4 m_rotationMatrix;
    Mat4 m_scaleMatrix;
    Mat4 m_modelMatrix;

    bool m_isTransformed;

    bool m_isRotated;
    bool m_isTranslated;
    bool m_isScaled;
};

} // namespace core