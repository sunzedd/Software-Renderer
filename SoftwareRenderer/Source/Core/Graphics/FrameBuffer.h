#pragma once
#include "Buffer.h"
#include "Color.h"

namespace core {

class FrameBuffer : public Buffer<sf::Color>
{
public:
    FrameBuffer(int width, int height)
        :
        Buffer(width, height)
    { }

    void setPixel(int x, int y, const Color& color)
    {
        Buffer::set(x, y, color.toSFMLColor());
    }

    const sf::Color* pixels() const
    {
        return m_pData.get();
    }
};

} // namespace core
