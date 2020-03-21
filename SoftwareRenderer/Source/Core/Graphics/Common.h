#pragma once
#include <vector>

namespace Core {
class Vec3;
class Vec2i;
class Vertex;

template <class T>
using Line = std::pair<T, T>;

typedef Line<Vec2i>		LineV2i;
typedef Line<Vec3>		LineV3;
typedef Line<Vertex>	LineVtx;
}