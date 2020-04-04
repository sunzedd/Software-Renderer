#pragma once
#include "IDrawable3D.h"
#include "ITransformable3D.h"
#include "Transform3D.h"

namespace core {

class Object3DBase : public IDrawable3D, public ITransformable3D
{
public:
    void toggleVisibility(bool enable) {
        m_isVisible = enable;
    }

    void toggleActivity(bool enable) {
        m_isActive = enable;
    }

    bool isActive() const {
        return m_isActive;
    }

    bool isVisible() const {
        return m_isVisible;
    }

    const Vec3& getPosition() const {
        return m_transform.getPosition();
    }

    const Vec3& getRotation() const {
        return m_transform.getRotation();
    }

    const Vec3& getScale() const {
        return m_transform.getScale();
    }

protected:
    Transform3D m_transform;

private:
    bool m_isVisible = true;
    bool m_isActive  = true;
};

} // namespace core 