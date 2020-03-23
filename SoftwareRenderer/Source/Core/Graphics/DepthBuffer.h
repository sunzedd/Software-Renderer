#pragma once
#include "Buffer.h"

#define DEFAULT_DEPTH_BUFFER_VALUE -100000.0f

namespace core {

class DepthBuffer : public Buffer<float>
{
public:
    DepthBuffer(int width, int height)
        :
        Buffer(width,height)
    {
        clear();
    }

    void clear() override
    {
        fill( DEFAULT_DEPTH_BUFFER_VALUE );
    }

    bool testAndSet(int x, int y, float z)
    {
        if(get(x, y) < z)
        {
            set(x, y, z);
            return true;
        }

        return false;
    }
};

} // namespace core
