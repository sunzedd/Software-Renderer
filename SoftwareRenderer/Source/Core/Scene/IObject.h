#pragma once

namespace core {

class IObject
{
public:
    virtual void update(unsigned int deltaTime) = 0;
};

} // namespace core