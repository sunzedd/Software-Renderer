#pragma once
#include "../../Core/Scene/Object3D.h"

class CubeScript final : public core::Script
{
public:
    void start() override
    {
        using namespace core;

        m_scriptable->setPosition(Vec3(0, 1, 0));
        m_scriptable->scale(Vec3(0.7, 0.7, 0.7));
    }

    void update(unsigned int deltaTime) override
    {
        using namespace core;

        const float dRotation = deltaTime * m_rotationSpeed;
        m_scriptable->rotate(Vec3::up() * dRotation);
    }

private:
    const float m_rotationSpeed = 0.05f;
};