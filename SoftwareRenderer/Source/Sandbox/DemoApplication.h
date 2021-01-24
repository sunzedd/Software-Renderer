#pragma once
#include <unordered_map>

#include "../Core/Engine.h"
#include "DemoAssets.h"

#define DEMO_WIDTH  800
#define DEMO_HEIGHT 600

class DemoApplication : public core::App 
{
public:
    DemoApplication();

private:
    void update(unsigned int deltaTime) override;
    void render() override;
    
    void createScene();
    void initCamera();

private:
    core::Camera m_camera;
    std::vector<std::shared_ptr<core::Object3DBase>> m_objects;
    std::vector<std::shared_ptr<core::Shader>> m_shaders;
    std::shared_ptr<core::Object3D> m_lighter;
};