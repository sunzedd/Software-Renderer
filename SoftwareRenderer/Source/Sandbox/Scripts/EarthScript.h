#pragma once
#include "../../Core/Scene/Object3D.h"

class EarthScript final : public core::Script
{
public:
    void start() override
    {
        using namespace core;

        m_scriptable->setPosition(Vec3(2, 4.5, 1));
    }

    void update(unsigned int deltaTime) override
    {
        using namespace core;

        const float dRotation = deltaTime * m_rotationSpeed;
        m_scriptable->rotate(Vec3(1, 1, 1) * dRotation);
    }

private:
    const float m_rotationSpeed = 0.03f;
};