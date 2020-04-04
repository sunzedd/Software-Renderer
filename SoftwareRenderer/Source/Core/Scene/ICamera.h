#pragma once
#include "../Math/Mat4.h"

namespace core
{

class ICamera
{
public:
    virtual const Mat4& getViewMatrix() const = 0;
    virtual const Mat4& getProjMatrix() const = 0;
};

} // namespace core