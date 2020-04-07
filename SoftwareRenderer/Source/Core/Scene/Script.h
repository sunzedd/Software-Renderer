#pragma once
#include <memory>

namespace core {

class Object3DBase;

class Script
{
public:
    void init(Object3DBase* scriptable) 
    {
        m_scriptable = scriptable;
        start();
    }

    virtual void start() = 0;
    virtual void update(unsigned int deltaTime) = 0;

protected:
    Object3DBase* m_scriptable = nullptr; // Script does not own an object3D.
};

} // namespace core