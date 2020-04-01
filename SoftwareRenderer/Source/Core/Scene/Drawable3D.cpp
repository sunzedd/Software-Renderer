#include "Drawable3D.h"

namespace core {

Transform3D& Drawable3D::getTransform()
{
    return m_transform;
}

void Drawable3D::setRenderMode(RenderMode mode)
{
    m_renderMode = mode;
}

void Drawable3D::rejectBackFaces(bool enable)
{
    m_rejectBackFaces = enable;
}

void Drawable3D::toogleVisibility(bool enable)
{
    m_isVisible = enable;
}

bool Drawable3D::isVisible() const
{
    return m_isVisible;
}

} // namespace core