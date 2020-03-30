#pragma once
#include "../Core/Engine.h"
#include "Shaders/GouraudShader.h"

#define DEMO_WIDTH 1024
#define DEMO_HEIGHT 724

class DemoApplication : public core::App
{
public:
    DemoApplication();

    void update(unsigned int deltaTime) override;
    void render() override;

private:
    core::Camera m_camera;
    std::vector<std::shared_ptr<core::DrawableGameObject>> m_objects;
    std::shared_ptr<core::PointLight> m_light;
};