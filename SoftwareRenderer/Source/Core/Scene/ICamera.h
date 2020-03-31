#pragma once
#include "../Math/Mat4.h"
#include "IObject.h"

namespace core
{

class ICamera : public IObject
{
public:
    virtual const Mat4& getViewMatrix() = 0;
    virtual const Mat4& getProjMatrix() = 0;
};

} // namespace core