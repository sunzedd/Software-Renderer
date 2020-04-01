#pragma once
#include "Object3D.h"

namespace core {

class Group3D : public Object3D
{
public:
    virtual void render(ICamera& camera) override;
    virtual void update(unsigned int deltaTime) override;

    void addChild(std::shared_ptr<Object3D> child);

protected:
    std::vector<std::shared_ptr<Object3D>> m_children;
};

} // namespace core