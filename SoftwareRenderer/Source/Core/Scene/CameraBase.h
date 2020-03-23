#pragma once
#include "../Math/Mat4.h"
#include "../Math/Vec3.h"

#include "Entity.h"

namespace core
{

class CameraBase : public Entity
{
public:
    virtual const Mat4& getViewMatrix() = 0;
    virtual const Mat4& getProjMatrix() = 0;
};

}