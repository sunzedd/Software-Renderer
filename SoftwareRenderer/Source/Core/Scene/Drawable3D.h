#pragma once
#include "IObject.h"
#include "Transform3D.h"
#include "ICamera.h"

namespace core {

enum class RenderMode
{
    WIREFRAME,
    FILLED
};

class Drawable3D : public IObject
{
public:
    virtual void render(ICamera& camera) = 0;

    Transform3D& getTransform();
    void setRenderMode(RenderMode mode);
    void rejectBackFaces(bool enable);
    void toogleVisibility(bool enable);
    bool isVisible() const;

protected:
    Transform3D m_transform;
    RenderMode m_renderMode = RenderMode::FILLED;

    bool m_rejectBackFaces = true;
    bool m_isVisible       = true;
};

} // namespace core