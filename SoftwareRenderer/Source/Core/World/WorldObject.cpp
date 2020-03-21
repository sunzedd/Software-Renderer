#include "WorldObject.h"

namespace Core {

WorldObject::WorldObject(const Vec3& pos /* = Vec3(0, 0, 0)*/)
	:
	m_pos(pos)
{
	m_isTransformed = true;
}

void WorldObject::move(const Vec3& delta)
{
	m_pos += delta;
	m_isTransformed = true;
}

void WorldObject::setPosition(const Vec3& position)
{
	m_pos = position;
	m_isTransformed = true;
}

}