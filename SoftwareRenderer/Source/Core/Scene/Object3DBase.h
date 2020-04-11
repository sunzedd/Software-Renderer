#pragma once
#include "IDrawable3D.h"
#include "ITransformable3D.h"
#include "Transform3D.h"
#include "Script.h"

namespace core {

class Object3DBase : public IDrawable3D, public ITransformable3D
{
public:
    void attachScript(std::shared_ptr<Script> script);
    void toggleVisibility(bool enable);
    void toggleActivity(bool enable);

    bool isActive() const;
    bool isVisible() const;
    bool hasScript() const;

    const Vec3& getPosition() const;
    const Vec3& getRotation() const;
    const Vec3& getScale() const;

protected:
    Transform3D m_transform;
    std::shared_ptr<Script> m_script;

private:
    bool m_isVisible = true;
    bool m_isActive  = true;
};

} // namespace core 