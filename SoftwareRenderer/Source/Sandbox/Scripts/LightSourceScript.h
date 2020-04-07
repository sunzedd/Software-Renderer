#pragma once
#include "../../Core/Scene/Object3D.h"

class LigthSourceScript final : public core::Script
{
public:
    void start() override
    {
        using namespace core;

        m_scriptable->setPosition(Vec3(0.0f, 3.0f, 2.0f));
        m_scriptable->setScale(Vec3(0.1f, 0.1f, 0.1f));
    }

    void update(unsigned int deltaTime) override
    {
        using namespace core;

        static const float minPositionY = 0.5f;
        static const float maxPositionY = 5.0f;
        static Vec3 velocity = Vec3::up() * m_movementSpeed;

        const float dMove = m_movementSpeed * deltaTime;

        if (m_scriptable->getPosition().y >= maxPositionY && m_movingUp)
        {
            velocity = -Vec3::up() * dMove;
            m_movingUp = false;
        }
        else if (m_scriptable->getPosition().y <= minPositionY && !m_movingUp)
        {
            velocity = Vec3::up() * dMove;
            m_movingUp = true;
        }
        
        velocity = velocity.normalized() * dMove;

        m_scriptable->move(velocity);
    }

private:
    const float m_movementSpeed = 0.002;
    bool m_movingUp = true;
};