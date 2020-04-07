#include "Color.h"

namespace core {

Color::Color()
    : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
{}

Color::Color(float r, float g, float b)
    : r(r), g(g), b(b), a(1.0f)
{}

Color::Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{}

Color::Color(const Vec3& color)
    : r(color.x), g(color.y), b(color.z), a(1.0f)
{}

Color::Color(const Vec4& color)
    : r(color.x), g(color.y), b(color.z), a(color.w)
{}

sf::Color Color::toSFMLColor() const
{
    sf::Color color;
    color.r = static_cast<sf::Uint8>(r * 255);
    color.g = static_cast<sf::Uint8>(g * 255);
    color.b = static_cast<sf::Uint8>(b * 255);
    color.a = static_cast<sf::Uint8>(a * 255);

    return color;
}

} // namespace core
