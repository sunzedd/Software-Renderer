#pragma once
#include "WorldObject.h"
#include "../Math/Mat4.h"

namespace Core {

enum class Direction
{
	Forward, Backward,
	Left, Right,
	Up, Down
};

class ICamera : public WorldObject
{
public:
	ICamera(const Vec3& pos = Vec3(0, 0, 0))
		:
		WorldObject(pos)
	{ }

	virtual const Mat4& getCameraMatrix() const = 0;
};

} // namespace Core