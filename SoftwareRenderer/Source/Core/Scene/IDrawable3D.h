#pragma once
#include "ICamera.h"

namespace core {

class IDrawable3D
{
public:
    virtual void render(const ICamera& camera) const = 0;
};

} // namespace core