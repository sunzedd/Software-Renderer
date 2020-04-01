#pragma once
#include <unordered_map>
#include "../Core/Engine.h"
#include "Shaders/PhongShader.h"

#define DEMO_WIDTH 1024
#define DEMO_HEIGHT 724

class DemoApplication : public core::App
{
public:
    DemoApplication();

    void update(unsigned int deltaTime) override;
    void render() override;

private:
    void _initScene();
    void _updateSceneLogic(unsigned int deltaTime);

private:
    core::Camera m_camera;
    std::unordered_map<std::string, std::shared_ptr<core::Object3D>> m_objects;
    std::shared_ptr<core::Object3D> m_lighter;
};