#pragma once
#include "../Math/Vec4.h"

namespace core {

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    Color(const Vec3& color);
    Color(const Vec4& color);

    Color& operator += (const Color& rhs);
    Color& operator -= (const Color& rhs);
    Color& operator *= (float val);
    Color& operator /= (float val);

    sf::Color toSFMLColor() const;
};

Color operator + (const Color& lhs, const Color& rhs);
Color operator - (const Color& lhs, const Color& rhs);
Color operator * (const Color& c, float val);
Color operator / (const Color& c, float val);

} // namespace core
