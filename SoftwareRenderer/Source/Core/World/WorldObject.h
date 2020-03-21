#pragma once
#include "../Math/Vec3.h"

namespace Core {

class WorldObject
{
public:
	WorldObject(const Vec3& pos = Vec3(0, 0, 0));

	const Vec3& getPosition() const { return m_pos; }

	virtual void update(unsigned int dtime) = 0;
	virtual void move(const Vec3& delta);

	void setPosition(const Vec3& position);

protected:
	Vec3 m_pos;
	bool m_isTransformed;
};

} // namespace Core