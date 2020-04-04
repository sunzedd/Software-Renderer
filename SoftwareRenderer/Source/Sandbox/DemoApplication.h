#pragma once
#include <unordered_map>
#include "../Core/Engine.h"
#include "Shaders/PhongShader.h"

#define DEMO_WIDTH  940
#define DEMO_HEIGHT 560

class DemoApplication : public core::App
{
public:
    DemoApplication();

private:
    void update(unsigned int deltaTime) override;
    void render() override;

    void _initScene();

    void _handleInput(unsigned int deltaTime);
    void _executeLogicScript(unsigned int deltaTime);

private:
    core::Camera m_camera;
    std::vector<std::shared_ptr<core::Object3DBase>> m_objects;
    std::vector<std::shared_ptr<core::ShaderProgram>> m_shaders;
    std::shared_ptr<core::Object3D> m_lighter;
};