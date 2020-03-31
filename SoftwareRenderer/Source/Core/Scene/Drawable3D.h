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

protected:
    Transform3D m_transform;
    bool m_rejectBackFaces;
    RenderMode m_renderMode = RenderMode::FILLED;
};

} // namespace core