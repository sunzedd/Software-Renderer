#pragma once
#include "Buffer.h"

namespace core {

template <typename T>
Buffer<T>::Buffer(int width, int height)
    :
    m_pData(std::make_unique<T[]>(static_cast<size_t>(width) *
                                  static_cast<size_t>(height)) ),
    m_width(width),
    m_height(height)
{
    clear();
}
 
template <typename T>
Buffer<T>::~Buffer()
{ }

template <typename T>
T Buffer<T>::get(int x, int y) const
{
    assert(x > -1);
    assert(y > -1);
    assert(x < m_width);
    assert(y < m_height);

    return m_pData.get()[m_width * y + x];
}

template <typename T>
void Buffer<T>::set(int x, int y, T value)
{
    assert(x > -1);
    assert(y > -1);
    assert(x < m_width);
    assert(y < m_height);

    /*if (x < 0 || y < 0 || x > m_width - 1 || y > m_height -1)
        return;*/

    m_pData.get()[m_width * y + x] = value;
}

template <typename T>
void Buffer<T>::clear()
{
    std::memset(m_pData.get(), 0, sizeof(T) * m_width * m_height);
}

template <typename T>
void Buffer<T>::fill(T value)
{
    T* const pDataRaw = m_pData.get();

    for (T* cur = pDataRaw;
        cur < pDataRaw + static_cast<size_t>(m_width) * static_cast<size_t>(m_height);
        cur++)
    {
        *cur = value;
    }
}

} // namespace core

