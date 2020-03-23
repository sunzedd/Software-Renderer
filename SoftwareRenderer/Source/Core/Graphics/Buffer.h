#pragma once
#include <memory>
#include <assert.h>

namespace core {

template <typename T>
class Buffer
{
public:
    Buffer(int width, int height);
    virtual ~Buffer();

    int width() const { return m_width; }
    int height() const { return m_height; }

    T get(int x, int y) const;
    void set(int x, int y, T value);

    virtual void clear();
    void fill(T value);

protected:
    std::unique_ptr<T[]> m_pData;
    int m_width;
    int m_height;
};

} // namespace core

#include "Buffer.hpp"
