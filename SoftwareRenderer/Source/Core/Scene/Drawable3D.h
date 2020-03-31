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
    virtual void render(const ICamera& camera) = 0;

    Transform3D& getTransform();
    void setRenderMode(RenderMode mode);
    void rejectBackFaces(bool enable);

protected:
    Transform3D m_transform;
    RenderMode m_renderMode;
    bool m_rejectBackFaces;
};

} // namespace core