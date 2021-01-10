#pragma once
#include "../Math/Vec3.h"
#include "../Math/Mat4.h"

namespace core {


class Transform3D
{
    enum class _TransformationType
    {
        Scaling,
        Rotation,
        Translation
    };

public:
    Transform3D();

    void move(const Vec3& delta);
    void rotate(const Vec3& delta);
    void scale(const Vec3& delta);

    const Vec3& getPosition() const;
    const Vec3& getRotation() const;
    const Vec3& getScale() const;

    void setPosition(const Vec3& position);
    void setRotation(const Vec3& angles);
    void setScale(const Vec3& scale);

    const Mat4& getModelMatrix() const;
    const Mat4& getTranslationMatrix() const;
    const Mat4& getRotationMatrix() const;
    const Mat4& getScaleMatrix() const;

    void update();
    void modifyMatrix(_TransformationType matrixType, const Mat4& multiplier);

private:
    void registerTransformation(_TransformationType transformationType);
    void resetTransformationFlags();

protected:
    Vec3 m_position;
    Vec3 m_rotation;
    Vec3 m_scale;

private:
    Mat4 m_modelMatrix;
    Mat4 m_translationMatrix;
    Mat4 m_rotationMatrix;
    Mat4 m_scaleMatrix;

    bool m_isTransformed = true;
    bool m_isRotated     = true;
    bool m_isTranslated  = true;
    bool m_isScaled      = true;
};


} // namespace core