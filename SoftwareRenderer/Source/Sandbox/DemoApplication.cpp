#include "DemoApplication.h"

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    m_camera.setPosition(core::Vec3(0, 0, 10.0f));
    m_light = std::make_shared<core::PointLight>();
    m_light->getTransform().position = { 0, 5.0f, 3.0f };
    m_light->getTransform().scale = { 0.1f, 0.1f, 0.1f };


    // TODO: Create object builder class
    auto susannMesh = core::AssetLoader::loadMesh("Assets\\Meshes\\susann.obj");
    auto susannShader = std::make_shared<GouraudShader>();
    auto susannObject = std::make_shared<core::DrawableGameObject>(susannShader);
    auto susannTexture = core::AssetLoader::loadImage("Assets\\Textures\\quads.jpg");
    susannShader->pointLight = m_light;
    susannObject->setMesh(susannMesh);
    susannObject->setTexture(susannTexture);
    m_objects.push_back(susannObject);

    auto terrainMesh = core::AssetLoader::loadMesh("Assets\\Meshes\\floor.obj");
    auto terrainShader = std::make_shared<GouraudShader>();
    auto terrainObject = std::make_shared<core::DrawableGameObject>(terrainShader);
    auto terrainTexture = core::AssetLoader::loadImage("Assets\\Textures\\floor.jpg");
    terrainShader->pointLight = m_light;
    terrainObject->setMesh(terrainMesh);
    terrainObject->setTexture(terrainTexture);
    terrainObject->getTransform().position = { 0.0f, -1.0f, 0.0f };
    terrainObject->getTransform().scale = { 0.3f, 0.3f, 0.3f };
    m_objects.push_back(terrainObject);

    auto cubeMesh = core::AssetLoader::loadMesh("Assets\\Meshes\\cube.obj");
    auto cubeShader = std::make_shared<GouraudShader>();
    auto cubeObject = std::make_shared<core::DrawableGameObject>(cubeShader);
    auto cubeTexture = core::AssetLoader::loadImage("Assets\\Textures\\grass_real.jpg");
    cubeShader->pointLight = m_light;
    cubeObject->setMesh(cubeMesh);
    cubeObject->setTexture(cubeTexture);
    cubeObject->getTransform().position = { -3.0f, 0.0f, 2.0f };
    cubeObject->getTransform().scale = { 0.5f, 0.5f, 0.5f };
    cubeObject->getTransform().rotation = { 0, 45, 0 };
    m_objects.push_back(cubeObject);
}

void DemoApplication::update(unsigned int deltaTime)
{
    for (auto& obj : m_objects)
        obj->update(deltaTime);

    m_camera.update(deltaTime);
    m_light->update(deltaTime);
}

void DemoApplication::render()
{
    core::RenderPipeline::instance().beginFrame();

    for (auto& obj : m_objects)
        obj->render(m_camera);

    m_light->render(m_camera);
}