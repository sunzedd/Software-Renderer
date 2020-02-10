#pragma once
#include "WorldObject.h"
#include "../Math/Mat4.h"

namespace Core
{
	class ICamera : public WorldObject
	{
	public:
		ICamera(const Vec3& pos = Vec3(0, 0, 0))
			:
			WorldObject(pos)
		{ }

		virtual const Mat4& getCameraMatrix() const = 0;
	};
}