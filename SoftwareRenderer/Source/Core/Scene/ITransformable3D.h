#pragma once
#include "../Math/Vec3.h"

namespace core {

class ITransformable3D
{
public:
    virtual void move(const Vec3& delta) = 0;
    virtual void rotate(const Vec3& angles) = 0;
    virtual void scale(const Vec3& scale) = 0;

    virtual void setPosition(const Vec3& position) = 0;
    virtual void setRotation(const Vec3& angles) = 0;
    virtual void setScale(const Vec3& scale) = 0;

    virtual void update(unsigned int deltaTime) = 0;
};

} // namespace core