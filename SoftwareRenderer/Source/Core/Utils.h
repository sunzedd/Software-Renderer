#pragma once

namespace core {

template <typename T>
T clamp(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}

template <typename T>
T clampNormalize(T value)
{
    return clamp<T>(value, 0.0, 1.0);
}

} // namespace core