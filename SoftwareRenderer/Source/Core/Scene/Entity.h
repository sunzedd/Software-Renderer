#pragma once
#include "../Math/Mat4.h"
#include "../Math/Vec3.h"

namespace core
{

class Entity
{
public:
    virtual void update(unsigned int deltaTime) = 0;

protected:
    bool m_isTransformed = true;
};

}