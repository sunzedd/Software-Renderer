#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Object3DBase.h"

namespace core {

class CompositeObject3D : public Object3DBase
{
    using Component = std::pair<std::string, std::shared_ptr<Object3DBase>>;

public:
    void render(const ICamera& camera) const override;
    void update(unsigned int deltaTime) override;

    void move(const Vec3& delta) override;
    void rotate(const Vec3& angles) override;
    void scale(const Vec3& scale) override;

    void setPosition(const Vec3& position) override;
    void setRotation(const Vec3& angles) override;
    void setScale(const Vec3& scale) override;

    void addComponent(std::string name, std::shared_ptr<Object3DBase> component);
    void removeComponent(const std::string& name);

private:
    std::vector<Component> m_components;
};


} // namespace core